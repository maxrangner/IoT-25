// #include "set.h"

// // --------------------
// // Grundmetoder
// // --------------------

// bool Set::empty() const {
//     // TODO
//     // Hint: return list_.isEmpty();
//     assert(false && "TODO: Set::empty");
//     return true;
// }

// std::size_t Set::size() const {
//     // TODO
//     // Hint: return static_cast<std::size_t>(list_.lengthOfList());
//     assert(false && "TODO: Set::size");
//     return 0;
// }

// bool Set::contains(Data x) const {
//     // TODO
//     // Hint: return list_.isInList(x) != 0;
//     (void)x;
//     assert(false && "TODO: Set::contains");
//     return false;
// }

// bool Set::add(Data x) {
//     // TODO
//     // Hint:
//     // if (contains(x)) return false;
//     // list_.addLast(x);
//     // return true;
//     (void)x;
//     assert(false && "TODO: Set::add");
//     return false;
// }

// bool Set::remove(Data x) {
//     // TODO
//     // Hint: return list_.removeElement(x) != 0;
//     (void)x;
//     assert(false && "TODO: Set::remove");
//     return false;
// }

// void Set::clear() {
//     list_.clearList();
// }

// void Set::print(FILE* out) const {
//     std::fputs("Set ", out);
//     list_.printList(out);
// }

// // --------------------
// // Set-operationer
// // --------------------
// //
// // Dessa blir �rena� tack vare List::forEachCtx.
// // forEachCtx anropar en callback f�r varje element och skickar �ven med
// // en kontextpekare (Ctx = Context) som callbacken kan anv�nda.
// // 
// // Vad �r en callback? En funktion som skickas som argument till en annan funktion.
// // Vad �r en kontext? Extra data som callbacken kan anv�nda f�r att g�ra sitt jobb.
// //
// // Nedan finns en tydlig struktur med kontext-structs + callbacks.
// // Du beh�ver fylla i TODO-delarna i union/snitt/diff.

// // 1) UNION: l�gg in allt fr�n a och b i resultatet (add tar hand om dubbletter)
// namespace {
//     struct UnionCtx {
//         Set* out;
//     };

//     void union_add_cb(Data x, void* ctx) {
//         auto* c = static_cast<UnionCtx*>(ctx);
//         c->out->add(x);
//     }

//     struct OtherCtx {
//         const Set* other;
//         Set* out;
//     };

//     void intersection_cb(Data x, void* ctx) {
//         auto* c = static_cast<OtherCtx*>(ctx);
//         if (c->other->contains(x)) {
//             c->out->add(x);
//         }
//     }

//     void difference_cb(Data x, void* ctx) {
//         auto* c = static_cast<OtherCtx*>(ctx);
//         if (!c->other->contains(x)) {
//             c->out->add(x);
//         }
//     }
// }

// Set Set::set_union(const Set& a, const Set& b) {
//     // TODO:
//     // - Skapa Set r
//     // - Iterera a och b med forEachCtx och l�gg in i r
//     //
//     // Hint:
//     // Set r;
//     // UnionCtx ctx{&r};
//     // a.list_.forEachCtx(union_add_cb, &ctx);
//     // b.list_.forEachCtx(union_add_cb, &ctx);
//     // return r;

//     (void)a; (void)b;
//     assert(false && "TODO: Set::set_union");
//     return Set{};
// }

// Set Set::set_intersection(const Set& a, const Set& b) {
//     // TODO:
//     // - Skapa Set r
//     // - Iterera a:
//     //     om b.contains(x) -> r.add(x)
//     //
//     // Hint:
//     // Set r;
//     // OtherCtx ctx{&b, &r};
//     // a.list_.forEachCtx(intersection_cb, &ctx);
//     // return r;

//     (void)a; (void)b;
//     assert(false && "TODO: Set::set_intersection");
//     return Set{};
// }

// Set Set::set_difference(const Set& a, const Set& b) {
//     // TODO:
//     // - Skapa Set r
//     // - Iterera a:
//     //     om !b.contains(x) -> r.add(x)
//     //
//     // Hint:
//     // Set r;
//     // OtherCtx ctx{&b, &r};
//     // a.list_.forEachCtx(difference_cb, &ctx);
//     // return r;

//     (void)a; (void)b;
//     assert(false && "TODO: Set::set_difference");
//     return Set{};
// }