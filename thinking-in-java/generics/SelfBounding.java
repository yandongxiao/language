//: generics/SelfBounding.java

class SelfB<T extends SelfB<T>> {
  T element;
  SelfB<T> set(T arg) {
    element = arg;
    return this;
  }
  T get() { return element; }
}

class A extends SelfB<A> {}
class B extends SelfB<A> {} // Also OK

class C extends SelfB<C> {
  C setAndGet(C arg) { set(arg); return get(); }
}

class D {}
// Can't do this:
class E extends SelfB<A> {}
// Compile error: Type parameter D is not within its bound

// Alas, you can do this, so you can't force the idiom:
class F extends SelfB {}

public class SelfBounding {
  public static void main(String[] args) {
    B a = new B();
    a.set(new A());
  }
} ///:~
