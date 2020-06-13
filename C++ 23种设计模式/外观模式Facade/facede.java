/*
外观模式的代码没有一种固定的形式，下面只是一个案例代码
有可能别的代码和这个千差万别，但是也可能属于外观模式
*/ 

//创建一个接口
public interface Shape{
	void draw();
}

// 这个是系统方面的实现
public class Rectangle implements Shape {
   @Override
   public void draw() {
      System.out.println("Rectangle::draw()");
   }
}
public class Square implements Shape {
   @Override
   public void draw() {
      System.out.println("Square::draw()");
   }
}
public class Circle implements Shape {
   @Override
   public void draw() {
      System.out.println("Circle::draw()");
   }
}
//==================================

public class ShapeMaker {
   private Shape circle;
   private Shape rectangle;
   private Shape square;
 
   public ShapeMaker() {
      circle = new Circle();
      rectangle = new Rectangle();
      square = new Square();
   }
 
   public void drawCircle(){
      circle.draw();
   }
   public void drawRectangle(){
      rectangle.draw();
   }
   public void drawSquare(){
      square.draw();
   }
}

// 用户使用
public class FacadePatternDemo {
   public static void main(String[] args) {
      ShapeMaker shapeMaker = new ShapeMaker();
 
      shapeMaker.drawCircle();
      shapeMaker.drawRectangle();
      shapeMaker.drawSquare();      
   }
}