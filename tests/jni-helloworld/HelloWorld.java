class HelloWorld {
  private native void print(String str);

  public static void main(String[] args) {
    new HelloWorld().print("Hello, world!");
  }

  static {
    System.loadLibrary("Hello");
  }
}
