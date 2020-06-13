/*建造者模式 -> 优化
定义：将一个复杂对象的构造和表示相分离,使得同样的构建过程(稳定)可以创建不同的表示（变化）
步骤：分步骤构建一个复杂的对象，分步骤是一个稳定的算法，但是复杂的对象经常变化*/

// 对象的表示
class House{
	//1. 占地面积
	//2. 体积多大
	//3. 外形
	// ...
}

// 对象的构造
class HouseBuilder{
public:
	House* GetResult(){
		return pHouse;
	}
	virtual ~HouseBuilder(){}
protected:
	House* pHouse;
	virtual void BuildPatr1() = 0;
	virtual void BuildPatr2() = 0;
	virtual void BuildPatr3() = 0;
	virtual void BuildPatr4() = 0;
	virtual void BuildPatr5() = 0;
};

// 石头房子
class StoneHouse:public House{

};
// 玻璃房子
class GlassHouse:public House{

};

// 房子的构建
class StoneHouseBuilder:public HouseBuilder{
protected:
	virtual void BuildPatr1(){
		//pHouse->Part1 = ...
	}
	virtual void BuildPatr2(){

	}
	virtual void BuildPatr3() {

	}
	virtual void BuildPatr4() {

	}
	virtual void BuildPatr5() {

	}
};

	
// 同样的构建过程，这个部分是稳定的
class HouseDirector{
public:
	HouseBuilder* pHouseBuilder;
	// 不同的指针构造的对象就会不同
	HouseDirector(HouseBuilder* pHouseBuilder){
		this->pHouseBuilder = pHouseBuilder;
	}

	// 这里的部分不能放在构造函数，因为里面有虚函数,虚函数不可以写在构造函数中
	// 因为子类在调用构造函数的时候，先调用基类，但是子类构造函数还没有完成就调用子类的方法，逻辑不通
	House* Construct(){
		pHouseBuilder->BuildPatr1();

		for(int i = 0;i < 4;++i){
			pHouseBuilder->BuildPatr2();
		}

		bool flag = pHouseBuilder->BuildPatr3();

		if(flag){
			pHouseBuilder->BuildPatr4();
		}

		pHouseBuilder->BuildPatr5();

		return pHouseBuilder->GetResult();
	}
};

int main(){
	House* pHouse = new StoneHouse();
	pHouse->Init();

	return 0;	
}