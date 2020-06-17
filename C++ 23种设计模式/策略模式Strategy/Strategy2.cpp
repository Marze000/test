/*某公司开发了一个鸭子游戏，里面会出现各种特点的鸭子：绿头鸭，红头鸭，橡皮鸭……
	用程序如何实现这些鸭子？ 看到这个场景问题，很容易想到，
	先定义一个所有鸭子的超类Duck，把公共方法和属性封装进去。
	例如，鸭子都会游泳，鸭子都有各自的外貌：


解决办法
1、如果我们把对子类进行重写覆盖，则维护量太大
2、如果对所有的鸭子特点实现算法，这样也很麻烦

3、采用组合的方法，不要使用继承
	3.1 找到应用中可能变化之处，把他们独立出来
	3.2 针对接口编程，而不是方法编程
	3.3 用组合代替继承
*/

//定义两个行为接口类
class FlyBehavior {
public:
	virtual void fly() =0;
};

class QuackBehavior {
public:
	virtual void quack()=0;
};

//实现飞行接口的不同行为类
class FlyNoWay:public FlyBehavior{
public:
	void fly(){
        cout<<"我不能飞……";
    }
};

class FlyWithWings :public FlyBehavior{
public:
	void fly(){
		cout<<"飞~~~";
    }
};

class FlyWithRocket :public FlyBehavior{
public:
	void fly(){
		cout<<"带上火箭筒，飞~~~";
    }
};

//实现鸭叫的不同行为类
class Quack :public QuackBehavior{
public:
	void quack(){
		cout<<"呱呱呱~";
    }
};

class Squeak :public QuackBehavior{
public:
	void quack(){
		cout<<"吱吱吱~";
    }
};

class MuteQuack :public QuackBehavior{
public:
	void quack(){
		cout<<"我不会叫……";
    }
};

//组合了实现接口类
class Duck {
protected:
	FlyBehavior* flyBehavior;
    QuackBehavior* quackBehavior;
public:
    void swim(){
    	cout<<"All duck can swim!";
    }
    // * 动态改变飞行行为
    void setFlyBehavior(FlyBehavior* flyBehavior) {
        this->flyBehavior = flyBehavior;
    }
    // 动态改变鸭叫行为
    void setQuackBehavior(QuackBehavior* quackBehavior) {
        this->quackBehavior = quackBehavior;
    }
    void performFly(){
        flyBehavior->fly();
    }
    void performQuack(){
        quackBehavior->quack();
    }
};

//不同的鸭子类
//绿头鸭
class MallarDuck :public Duck{
public:
    MallarDuck() {
        //可飞
        flyBehavior = new FlyWithWings();
        //呱呱叫
        quackBehavior = new Quack();
    }

    void display() {
    	cout<<"看着像绿头鸭";
    }
};

/**
 * 绿头鸭
 */
class RedHeadDuck:public Duck{
public:
    RedHeadDuck() {
        //可飞
        flyBehavior = new FlyWithWings();
        //呱呱叫
        quackBehavior = new Quack();
    }

    void display() {
        System.out.println("看着像红头鸭");
    }
};

/**
 * 橡皮鸭
 */
class RubberDuck :public Duck{
public:
    RubberDuck() {
        //不会飞
        flyBehavior = new FlyNoWay();
        //吱吱叫
        quackBehavior = new Squeak();
    }

    void display() {
        System.out.println("看着像橡皮鸭");
    }
};

int main(){
	// 橡皮鸭
	Duck* d = new Duck();
	d->setQuackBehavior(new RubberDuck());
	d->setFlyBehavior(new RubberDuck());

	return 0;
}