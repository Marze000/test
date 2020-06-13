/*
建造者模式
定义：将一个复杂对象的构造和表示相分离,使得同样的构建过程(稳定)可以创建不同的表示（变化）
*/
class House{
public:
	void Init(){
		this->BuildPatr1();

		for(int i = 0;i < 4;++i){
			this->BuildPatr2();
		}

		bool flag = this->BuildPatr3();

		if(flag){
			this->BuildPatr4();
		}

		this->BuildPatr5();
	}

	virtual ~House(){}

protected:
	virtual void BuildPatr1() = 0;
	virtual void BuildPatr2() = 0;
	virtual void BuildPatr3() = 0;
	virtual void BuildPatr4() = 0;
	virtual void BuildPatr5() = 0;
}

// 石头房子
class StoneHouse:public House{
protected:
	virtual void BuildPatr1(){

	}
	virtual void BuildPatr2(){

	}
	virtual void BuildPatr3() {

	}
	virtual void BuildPatr4() {

	}
	virtual void BuildPatr5() {

	}
}
int main(){
	House* pHouse = new StoneHouse();
	pHouse->Init();

	return 0;	
}