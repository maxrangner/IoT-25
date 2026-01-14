// #ifndef SET_H
// #define SET_H

// #include "list.h"
// #include <assert.h>
// #include <stdio.h>

// /*
//   Set – mängd utan dubbletter

//   Invariant:
//   - Varje värde får förekomma max en gång.

//   Tips:
//   - contains(x) kan använda list_.isInList(x)
//   - add(x) ska bara lägga till om x inte redan finns
//   - remove(x) kan använda list_.removeElement(x)

//   Set-operationer (union/snitt/diff):
//   - Kräver traversal av elementen. Därför har List forEachCtx.

//   Ctx = "Context" (kontext):
//   - en void*-pekare som skickas med till callbacken så att callbacken kan
//     komma åt extra data (t.ex. en pekare till result-set och/eller andra set).
// */

// class Set {
// public:
//     using Data = ::Data;

//     Set() = default;

//     // TODO: ska fungera
//     bool empty() const;

//     // TODO: ska stämma
//     std::size_t size() const;

//     // TODO: true om x finns
//     bool contains(Data x) const;

//     // TODO:
//     // - om x redan finns: return false
//     // - annars: lägg till och return true
//     bool add(Data x);

//     // TODO: ta bort om finns, return true/false
//     bool remove(Data x);

//     // Färdig hjälpfunktion (för test)
//     void clear();

//     // Färdig hjälpfunktion (för test)
//     void print(FILE* out = stdout) const;

//     // TODO: mängdoperationer
//     static Set set_union(const Set& a, const Set& b);
//     static Set set_intersection(const Set& a, const Set& b);
//     static Set set_difference(const Set& a, const Set& b);

// private:
//     List list_;
// };

// #endif
