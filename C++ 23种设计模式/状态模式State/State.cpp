enum NetworkState{
	Network_Open,
	Network_Close,
	Network_Connect,
	//增加
	Network_Wait;
};

class NetworkProcessor{
	NetworkState state;
public:
	NetworkProcessor();
	void Operation1(){
		if(state == Network_Open){
			//****
			state = Network_Close;
		}
		else if(state == Network_Close){
			//.....
			state = Network_Connect;
		}
		else if(state == Network_Connect){
			state = Network_Open;
		}
	}
	void Operation2(){
		if(state == Network_Open){
			//...
			state = Network_Connect;
		}
		else if(state == Network_Close){
			//.....
			state = Network_Open;
		}
		else if(state == Network_Connect){
			//....
			state = Network_Close;
		}
	}
	~NetworkProcessor();
	
};