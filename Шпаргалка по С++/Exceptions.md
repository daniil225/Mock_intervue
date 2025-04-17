Конспект лекциий

[Lecture 4. Exceptions, part 1](https://www.youtube.com/watch?v=S_RccdgzjSA&list=PL3BR09unfgcgJPQZKaacwzGmcXMtEA-19&index=5)


# Обриуем проблему

Итак в стиле языка С у нас есть несколько вариантов обработки ошибок. 

- Возврат кода
- Выставить errno
- Передать дополнительный параметр что бы получить результат выполнения

Каждый из таких методов довольно неудобен и результат очень легко проигноррировать, в добавок не всегда можно возвращать коды возвратов

Приведу пример довольно опасного варианта кода:

```c++
template<typename T> class MyVector
{
    T* arr = nullptr;
    size_t size, used;
public:
    MyVector(size_t sz): size(sz), used(0)
    {
        arr = (T*) malloc(sz * sizeof(T));
        ...
    }
};
```

Здесь есть существенная проблема: может получиться так, что `arr = nullptr` и класс приходит в некорректное состояние (состояние которое не UB) но при этом классом пользоваться нельзя, он сломан.

Можно попробовать решить эту проблему так: в стиле `iostream`

```c++
template<typename T> class MyVector
{
    T* arr = nullptr;
    size_t size, used;
    bool valid_;
public:
    MyVector(size_t sz): size(sz), used(0), valid_(true)
    {
        arr = (T*) malloc(sz * sizeof(T));
        if(!arr) valid = false;
        ...
    }

    bool is_valid() const { return valid_; }
};
```

Но здесь тоже есть много проблема, во первых нужно проверять постоянно, а второе если будет что-то вот такое то такой трюк уже не пройдет:

```c++
Matrix operator+(Matrix a, Matrix b); 
```

Здесь неоткуда вернуть код возврата. И так как это отдельная функция здесь негде сохранить goodbit. 


## Типы передачи управления

- Локальная передача управления
    - условные операторы
    - циклы
    - локальный goto
    - прямой вызов функции и возврат из них

- Нелокальная передача управления
    - нелокальный longjmp и вычисляемый goto
    - косвенный ввызов функции (например по указателю)
    - переключение контекста потоков
    - исключения
    - сопрограммы 

# Что такое исключения? 

- Исключительные ситуации уровня аппаратуры (например undefined instruction exception). Это как взрыв вулкана и все плохо. Больше похоже на abort
- Исключительные ситуации уровня операционной системы (например data page fault)
- Исключения С++ (они нам далее интересны)

## Исключительные ситуации 

- Ошибки исключительными ситуациями не являются
    - рантайм ошибки, после которых состояние не востановимо (segmentaition fault)
    - ошибки контракта функции (assertion failure из-за неверных аргументов, невыполнение предусловия вызова)

- Исключительные ситуации
    - Состояние программы должно быть востановимо (например: исчерпание памяти или отстутвие файла на диске)
    - Исключительная ситуация не может быть обработана на том уровне, на котором возникла (программа сортировки не обязана знать, что делать при нехватке памяти на временный буфер)

## Больше про throw

Конструкция `throw <exception>` означает следующее
    - Создать объект исключения 
    - Начать размотку стека

Исключения отличаются от ошибок тем, что их нужно ловить. 

## Некоторые правила ловли исключений

- Ловля происходит по точному типу

```c++
try { throw 1; } catch(long l) {} // не поймали
```

- или по ссылке на точный тип 

```c++
try { throw 1; } catch(const int& ci) {} // поймали
```

- или по указателю на точный тип

```c++
try { throw new int(1); } catch(int* pi) {} // поймали
```

- или по ссылке или указателю на базовый класс

```c++
try { throw Derived(); } catch(Base& b) {} // поймали
```

- Catch- блоки пробуются в порядке перечисления 
- Пойманую переменную можно менять или удалить

```c++
try { throw new Derived(); } catch(Base* b) { delete b; } // ok
```

- Пойманное исключение можно перевыбросить

```c++
try { throw new Derived(); } catch(Base& b) {throw;} // ok
```

## Некоторые неприяности

```c++
class MathErr {};
class Overflow: public MathErr {};

try
{

}
catch(MathErr e) { Обработка всех ошибок.}; // Slicing! Производный класс при передаче по значению срежется до базового. 
catch(Overflow e) {}
```

Избегание неприятностей

```c++
try
{

}
// 1. Правильный порядок: от частного к общему
// 2. Ловим строго по косвенности
catch(Overflow& e) {}
catch(MathErr& e) {}
```

## Множественное наследование

```c++
struct my_exc1: exception {};
struct my_exc2: exception {};

struct your_exc3: my_exc1, my_exc2 {}

int main()
{
    try { throw your_exc3(); }
    catch(exception const& e) { cout << e.what(); }
    catch(...) { cerr << "whops"; } // Вызовется вот это, так как в your_exc3 2 экземляра класса exception и компиялтор не знает какой ему выбрать. 
}
```

Эта проблема решается при помощи `virtual` базовых классов. Виртуальном наследовании. 

## Нейтральность

Не надо перехватывать те исключения, которые мы не может обработать

```c++
try
{

}
catch(...){} // Это убивает нейтральность
```

# Гарантии безопасности исключений 

- Базовая гарантия: исключения при выполнении операции может изменить состояние программы, но не вызывает утечек и оставлает все объекты в согласованном (но не обязательно предсказуемом) состоянии. 
- Стогая гарантия: при исключении гарантируется неизменность состояния программы относительно задействованных в операции объектов (commit/rollback)
- Гарантия бесбойности: функции не генерируют исключений (noexcept)

# Рассмотрим проблему написания конструктора копирования

```c++
template<typename T> class MyVector
{
    T* arr_ = nullptr;
    size_t size_, used_;

public:
    MyVector(size_t sz): size(sz), used(0)
    {
        arr_ = new T[sz]; // бросает bad_alloc
    }
};
```

## Первый вариант

```c++
template<typename T> class MyVector
{
    T* arr_ = nullptr;
    size_t size_, used_;

public:
    MyVector(const MyVector& rhs)
    {
        arr_ = new T[rhs.size_]; // здесь утечка памяти
        size_ = rhs_.size; used_ = rhs.used_;
        for(size_t i = 0; i != rhs.size_; i++)
            arr_[i] = rhs.arr_[i]; // если здесь исключение, например у нас был вектор векторов 
    }
};
```

## Попытка номер 2

```c++
template<typename T>
T *safe_copy(const T* src, size_t srcsize)
{
    T* dest = new T[srcsize]; // Если летит исключение то ок 
    try
    {
        for(size_t idx = 0; idx != srcsize; ++idx)
            dest[idx] = src[idx]; // Если здесь полетит, то все нормально
    }
    catch(...)
    {
        delete[] dest;
        throw;
    }

    return dest;
}

// Далее мы ее используем в коде констурктора копирования
```

Такой код предоставляет базовую гарантию безопасности. Но выглядит такое решение не очень хорошо

Следующий шаг-это оператор присваивания

```c++
MyVector& operator=(const MyVector& rhs)
{
    if(this == &rhs) return *this;
    delete arr_; // Это плохо, потому что мало ли из safe_copy полетит исключение, и у нас получится объект в несогласованном состоянии, что плохо
    arr_ = safe_copy(rhs.arr_, rhs.size_);
    size_ = rhs.size_; used_ = rhs.used_;
    return *this;
}

// Переставим строчки местами и получим результата следующий 
MyVector& operator=(const MyVector& rhs)
{
    if(this == &rhs) return *this;
    T* narr_ = safe_copy(rhs.arr_, rhs.size_);
    delete arr_;
    arr_ = narr;
    size_ = rhs.size_; used_ = rhs.used_;
    return *this;
}
```

Это конечно работает, но выглядит как-то хрупко и криво. 

Но там дублирование, так как там переписанные конструкторы копирования и деструктор. 

Итак еще одна порытка:

```c++
template<typename T> class MyVector
{
    T* arr_;
    size_t size_, used_;

public:
    // Гаоантия безбойности 
    static void swap(MyVector& lhs, MyVector& rhs) noexcept
    {
        std::swap(lhs.arr_, rhs.arr_);
        std::swap(lhs.size_, rhs.size_);
        std::swap(lhs.used_, rhs.used_);
    }

    MyVector(const MyVector& rhs)
    {
        arr_ = safe_copy(rhs.arr_, rhs.size_);
        size_ = rhs.size_; used_ = rhs.used_;
    }

    MyVector& operator=(const MyVector& rhs)
    {
        MyVector tmp(rhs); // Конструктор копирования
        swap(this, tmp);
        return *this;
    }
};
```

## Извлечение из массива

```c++
template<typename T> class MyVector
{
    T* arr;
    size_t size_, used_;
public:
    T pop()
    {
        assert(used_ > 0);
        T result = arr[used_ - 1]; // Если исключение летит, то все нормально временная переменная не будет создана
        used_ -= 1;
        return result;
    }
};
```

Однако код довольно плох. Посмотрим на применение класса:

```c++
MyVector<SomeType> v;

SomeType s = v.pop(); // исключение при копировании элемента. 
```

Получается так, что элемент в `MyVector` мы потеряли, но в переменную он не пришел

Именно поэтому нужно писать так:

```c++
template<typename T> class MyClass
{
    T* arr_;
    size_t size_, used_;
public:
    T top()
    {
        assert(used > 0);
        return arr[used-1];
    }

    void pop()
    {
        assert(used_ > 0);
        used_ -= 1;
    }
};
```


# Проектированние классов с учетом исключений

Основной идеей явлается разделить управление памятью и реализацию логики на 2 независимых объекта. 

- Класс работающий с сырой памятью
- Использующий объекты этого класса внешний класс, работающий с типизированным содержимым

Для этого часто используется управление памятью вручную через нестандартные формы `new` и `delete` 

Для примера рассмотрим примерчик:

```c++
T& operator=(T const& x)
{
    if(this != &x)
    {
        this->~T();      
        new (this) T(x); // частичная перезапись. Может полететь исключение, что вызовет double delete 
    }
    return *this;
}
```

У такого оператора отсутсвует даже базовая гарантия безопасности. 

## Полезные helpers

```c++
template<typenmae T>
void copy_construct(T* p, const T& val)
{
    new (p) T(val);
}

template<typename T>
void destroy(T* p)
{
    p->~T();
}

template<typename FwsIter>
void destroy(FwdIter first, FwdIter last)
{
    while(first != last)
        destroy(&*first++);
}
```

### Правило для деструкторов

Исключения не должны покидать деструктор. Если это произошло, то будет незамедлительно вызван `std::terminate`

## Идея построения класса со строгой гарантией безопасности 

1. Создаем класс `MyVectorBuf`, который будет заниматься выделением и очисткой памяти через операторы `::operator new` и `::operator delete` 
2. Пишем класс `MyVector: protected MyVectorBuf`, и все операции выделения памяти делегируем классу наследнику, а внктри уже просто вызываем когда это потребуется. 

# Жизнь без исключений

Ну можно использовать `system_error` для того, что бы коды ошибок объединять в общие семантические группы. 

# Про оператор noexcept

Для более тонкой настройки бросания исключения для функции можно использовать оператор `noexcept`

```c++
template<class T>
T copy(T const& original) noexcept(noexcept(T(original)))
{
    return original;
}
```

Оператор `noexcept` возвращает `true` или `false` в зависимости от вычисления выражения под ним на этапе компиляции. 

Примеры:

```c++
struct ThrowingCtor { ThrowingCtor() {} };
void foo(ThrowingCtor) noexcept;
void foo(int) noexcept;
assert(noexcept(foo(1)) == true);
assert(noexcept(foo(ThrowingCtor{})) == false);
```

Важно отметить, что `noexcept` ничего не вычислает и не проверает что что-то будет выполняться.
Например:

```c++
void increment(int&) noexcept;
assert(noexcept(increment(*((int*)0))) == true);
```

Выражение будет истменным, даже несмотря на то, что это UB для выполнения. 
