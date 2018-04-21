//: generics/ErasureAndInheritance.java

class GenericBase<T> {
  private T element;
  public void set(T arg) { arg = element; }
  public T get() { return element; }
}

class Derived1<T> extends GenericBase<T> {}

class Derived2 extends GenericBase {} // No warning

// class Derived3 extends GenericBase<?> {}
// Strange error:
//   unexpected type found : ?
//   required: class or interface without bounds

public class ErasureAndInheritance {
  public static void main(String[] args) {
    Derived1<Integer> d2 = new Derived1<>();
    Integer obj = d2.get();
  }
} ///:~
