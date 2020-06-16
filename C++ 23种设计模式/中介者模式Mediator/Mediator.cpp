// 聊天室，多个对象可以向聊天室发消息，聊天室向多个对象发消息

// 创建中介类。
class ChatRoom {
public:
   static void showMessage(User user, String message){

      cout<<new Date().toString()<<"[" <<user.getName()<<"]"<<message<<endl;
   }
}

//创建 user 类。
class User {
private:
   string name;
 
public:
   string getName() {
      return name;
   }
 
   void setName(string name) {
      this->name = name;
   }
 
   User(string name){
      this->name  = name;
   }
 
   void sendMessage(string message){
      ChatRoom.showMessage(name,message);
   }
}

//使用 User 对象来显示他们之间的通信。
int main(){
   User robert = new User("Robert");
   User john = new User("John");

   robert.sendMessage("Hi! John!");
   john.sendMessage("Hello! Robert!");
}

//执行程序，输出结果：
Thu Jan 31 16:05:46 IST 2013 [Robert] : Hi! John!
Thu Jan 31 16:05:46 IST 2013 [John] : Hello! Robert!