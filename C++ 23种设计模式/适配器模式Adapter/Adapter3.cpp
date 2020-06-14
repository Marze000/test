//为媒体播放器和更高级的媒体播放器创建接口。
class MediaPlayer {//媒体播放器
public:
    virtual void play(string audioType, string fileName)=0;
};

class AdvancedMediaPlayer { //更高级的播放器
public:
   virtual void playVlc(string fileName) = 0;
   virtual void playMp4(string fileName) = 0;
};

//创建实现了 AdvancedMediaPlayer 接口的实体类。
class VlcPlayer :public AdvancedMediaPlayer{
public:
   void playVlc(string fileName) {
      //...
      cout<<"Playing vlc file.name"<<fileName<<endl;
   }
 
   void playMp4(string fileName) {
      //...
   }
};

class Mp4Player:public AdvancedMediaPlayer{
public:
   void playVlc(string fileName) {
      //什么也不做
   }
 
   void playMp4(string fileName) {
      cout<<"Playing mp4 file.name"<<fileName<<endl;
   }
};

//创建实现了 MediaPlayer 接口的适配器类。
class MediaAdapter:public MediaPlayer {
public:
   AdvancedMediaPlayer*  advancedMusicPlayer;

   MediaAdapter(string audioType){
      if(audioType.equals("vlc") ){
         advancedMusicPlayer = new VlcPlayer();       
      } 
      else if (audioType.equals("mp4")){
         advancedMusicPlayer = new Mp4Player();
      }  
   }
 
   void play(string audioType, string fileName) {
      if(audioType.equals("vlc")){
         advancedMusicPlayer->playVlc(fileName);
      }
      else if(audioType.equals("mp4")){
         advancedMusicPlayer->playMp4(fileName);
      }
   }
}

//创建实现了 MediaPlayer 接口的实体类。
class AudioPlayer :public MediaPlayer {
public:
   MediaAdapter* mediaAdapter; 
 
   void play(String audioType, String fileName) {    
 
      //播放 mp3 音乐文件的内置支持
      if(audioType.equals("mp3")){
         cout<<"Playing mp3 file. Name: "<< fileName;         
      } 
      //mediaAdapter 提供了播放其他文件格式的支持
      else if(audioType.equalsIgnoreCase("vlc") 
         || audioType.equalsIgnoreCase("mp4")){

         mediaAdapter = new MediaAdapter(audioType);
         mediaAdapter->play(audioType, fileName);
      }
      else{
         cout<<"Invalid media"<<audioType<<"format not supported"<<endl;
      }
   }   
}

//播放不同类型的音频格式。
int main(){
   AudioPlayer* audioPlayer = new AudioPlayer();

   audioPlayer->play("mp3", "beyond the horizon.mp3");
   audioPlayer->play("mp4", "alone.mp4");
   audioPlayer->play("vlc", "far far away.vlc");
   audioPlayer->play("avi", "mind me.avi");

}

//执行程序，输出结果：
Playing mp3 file. Name: beyond the horizon.mp3
Playing mp4 file. Name: alone.mp4
Playing vlc file. Name: far far away.vlc
Invalid media. avi format not supported