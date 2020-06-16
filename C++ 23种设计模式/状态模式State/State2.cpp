class NetworkState{
public:
	NetworkState* PNext;
	virtual void Operator1() = 0;
	virtual void Operator2() = 0;
	virtual void Operator3() = 0;
	NetworkState();
	virtual ~NetworkState(){}
	
};

class OpenState:public NetworkState{
	static NetworkState* m_instance;
public:
	static NetworkState* getInstance(){
		if(m_instance == nullptr){
			m_instance = new OpenState();
		}
		return m_instance;
	}
	void Operator1(){
		//.....
		PNext = CloseState::getInstance();
	}
	void Operator2(){
		//...
		PNext = ConnectState::getInstance();
	}
	void Operator3(){
		PNext = OpenState::getInstance();
	}
};
//
class CloseState:public NetworkState{};
class ConnectState:public NetworkState{};

class NetworkProcess{
	NetworkState* pState;
public:
	NetworkProcess(NetworkState* pState){
		this->pState = pState;
	}
	void Operator1(){
		//...
		pState->Operator1();
		pState = pState->PNext;
	}
	void Operator2(){
		//...
		pState->Operator2();
		pState = pState->PNext;
	}
	void Operator3(){
		//...
		pState->Operator3();
		pState = pState->PNext;
	}
	
};