class Isubject{
public:
	Isubject();
	virtual void process();
	~Isubject();
	
};
// Proxt 设计比较复杂
class SubjectProxy:public Isubject{
public:
	virtual void process(){
		//...
		
		// 对 RealSubject 的一种间接访问
	}
};
class ClientApp{
	Isubject* subject;
public:
	ClientApp(){
		subject = new SubjectProxy();
	}
	void DoTask(){
		// ...
		subject->process();
		// ...
	}
};