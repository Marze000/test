//创建一个接口。
class State {
public:
	virtual void doAction(Context context) = 0;
};

//创建实现接口的实体类。
class StartState:public State {
public:
	void doAction(Context* context) {
		cout<<"Player is in start state"<<endl;
      	context->setState(this); 
   	}
   	string toString(){
    	return "Start State";
   	}
};

class StopState:public State {
public:
	void doAction(Context* context) {
		cout<<"Player is in stop state"<<endl;
	    context->setState(this); 
   	}
 
   	string toString(){
    	return "Stop State";
   	}
};

//创建 Context 类。
class Context {
private:
	State* state;
 
public:
	Context(){
    	state = null;
   	}
 
   	void setState(State state){
    	this->state = state;     
   	}
 
  	State getState(){
    	return state;
   	}
}

//查看当状态 State 改变时的行为变化。
int main(){
	Context* context = new Context();
	StartState* startState = new StartState();
	startState->doAction(context);
	cout<<context->getState()->toString()<<endl;

	StopState* stopState = new StopState();
	stopState->doAction(context);
	cout<<context->getState()->toString()<<endl;
}
	

//执行程序，输出结果：
Player is in start state
Start State
Player is in stop state
Stop State