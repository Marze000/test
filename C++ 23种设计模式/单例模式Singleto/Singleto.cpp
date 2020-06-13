class Singleton{
private:
	Singleton();
	Singleton(const Singleton& other);

public:
	~Singleton(){}
	static Singleton* getInstance();
	static Singleton* m_instance;
};

Singleton::m_instance = nullptr;

// 版本1 (线程不安全)
Singleton* Singleton::getInstance(){
	if(m_instance == nullptr){
		m_instance = new Singleton();
	}
	return m_instance;
}

// 版本2  加锁:代表太高,
Singleton* Singleton::getInstance(){
	Lock lock; // 获取锁，函数结束后锁自动释放
	if(m_instance == nullptr){
		m_instance = new Singleton();
	}
	return m_instance;
}

// 版本3 双检查锁,缓解了版本 2 锁的代价
//               但是内存reorder 不安全
Singleton* Singleton::getInstance(){
	if(m_instance == nullptr){
		// 如果没有第二个判断，这行代码可能会有多个线程执行到
		Lock lock;
		// 第二个判断不可以去掉,如果去掉，Lock 相当于摆设
		if(m_instance == nullptr){
			m_instance = new Singleton();
		}
	}
	return m_instance;
}
/* m_instance = new Singleton(); 这行代码按照我们正常的执行顺序是
  1. operator new 函数在内存划分一块地址
  2. 调用构造器，进行内存的初始化
  3. 然后把内存的首地址返回给 m_instance
  但是CPU 可能会把第2步和第3步调换顺序，还没有执行构造器就把地址返回给m_instance
  这样一来，如果另一个线程也进入到函数内部，会返回 m_instance,这个指针是不可以用的
*/

// 版本4  在类中对 m_instance 进行声明 volatile static Singleton* m_instance;
// 		  防止变量被编译器优化到寄存器
Singleton* Singleton::getInstance(){
	if(m_instance == nullptr){
		// 如果没有第二个判断，这行代码可能会有多个线程执行到
		Lock lock;
		// 第二个判断不可以去掉,如果去掉，Lock 相当于摆设
		if(m_instance == nullptr){
			m_instance = new Singleton();
		}
	}
	return m_instance;
}