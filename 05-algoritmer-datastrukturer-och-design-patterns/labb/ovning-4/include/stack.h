// #ifndef STACK_H
// #define STACK_H

// #include "list.h"
// #include <assert.h>
// #include <stdio.h>

// /*
//   Stack – LIFO

//   Representation:
//   - Toppen på stacken motsvarar listans första element.

//   Mappning:
//   - push(x)  -> list.addFirst(x)
//   - peek()   -> list.getFirstElement()
//   - pop()    -> getFirstElement() + removeFirst()
// */

// class Stack {
// public:
//     using Data = ::Data;

//     Stack() = default;

//     // TODO: ska fungera
//     bool empty() const;

//     // TODO: ska stämma
//     std::size_t size() const;

//     // TODO: lägger value överst
//     void push(Data value);

//     // TODO: returnerar översta utan att ta bort (assert om tom)
//     Data peek() const;

//     // TODO: tar bort + returnerar översta (assert om tom)
//     Data pop();

//     // Färdig hjälpfunktion (för test)
//     void clear();

//     // Färdig hjälpfunktion (för test)
//     void print(FILE* out = stdout) const;

// private:
//     List list_;
// };

// #endif
