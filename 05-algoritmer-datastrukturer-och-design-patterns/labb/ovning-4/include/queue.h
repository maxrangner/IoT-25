// #ifndef QUEUE_H
// #define QUEUE_H

// #include "list.h"
// #include <assert.h>
// #include <stdio.h>

// /*
//   Queue – FIFO

//   Representation:
//   - Front i kön motsvarar listans första element.
//   - Enqueue lägger sist.

//   Mappning:
//   - enqueue(x) -> list.addLast(x)
//   - peek()     -> list.getFirstElement()
//   - dequeue()  -> getFirstElement() + removeFirst()
// */

// class Queue {
// public:
//     using Data = ::Data;

//     Queue() = default;

//     // TODO: ska fungera
//     bool empty() const;

//     // TODO: ska stämma
//     std::size_t size() const;

//     // TODO: lägger value sist
//     void enqueue(Data value);

//     // TODO: returnerar första utan att ta bort (assert om tom)
//     Data peek() const;

//     // TODO: tar bort + returnerar första (assert om tom)
//     Data dequeue();

//     // Färdig hjälpfunktion (för test)
//     void clear();

//     // Färdig hjälpfunktion (för test)
//     void print(FILE* out = stdout) const;

// private:
//     List list_;
// };

// #endif
