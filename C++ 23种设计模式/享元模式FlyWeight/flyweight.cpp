// 把字体实现为一种对象
class Font{
public:
	Font(const string& key)	{

	}
	~Font();
private:
	string key;
};

class FontFactory{
private:
	map<string,Font*>fontPool; // 字体池
public:
	Font* GetFont(const string& key){
		map<string,Font*>::iterator item = fontPool.find(key);

		if(item != fontPool.end()){
			return fontPool[key];
		}
		else{
			Font* font = new Font(key);
			fontPool[key] = font;
		}
		return font;
	}
	void clear(){
		//...
	}
};