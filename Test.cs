using System;

public class Test {
    public Test() {
        Console.WriteLine("Constructor");
    }

    public int Add(int a, int b) {
        return a + b;
    }

    public static void Hello() {
        Console.WriteLine("Hello from the static method");
    }

    public static void Main() {
        Console.WriteLine("Hello from Main");
    }
}