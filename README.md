Git 相关的指令

  (1)  git init 初始化 git 仓库
  (2)  git add filename 把这个文件移动缓存区，filename 等待被提交
       git rm --cached 移除缓存
  (3)  git commit -m "提交日志"  提交信息
  (4)  git status 提交状态
  (5)  git log 查看所有产生的 commit 记录
  (6)  git branch a 新建一个名字为 a 的分支(默认是 master 主分支)
  (7)  git checkout a 切换到 a 的分支
  (8)  git checkout -b b  新建一个b 分支，自动切换到 b 分支.
  (9)  git merge a 把 a 分支的代码合并过来
  (10) git branch -d a 删除 a 分支  git branch -D a 强行删除
  (11) git tag 给代码加标签 

   向 Github 提交代码
   (1) ssh 需要在本地和远程进行 ssh 密码的配对
       ssh-keygen -t rsa 按照 rsa 算法生成密码
       会自动保存到 id_rsa 和 id_rsa.pub 文件中
       把密码添加到远程的 Key 中
   (2) git push origin master 把本地提交到 master 分支
   (3) git pull origin master 把远程最新代码更新到本地(先 pull 再 push)
   (4) git clone git@github.com:Marze000/test.git 克隆项目
   (5) git remote -v 查看当前项目有哪些远程仓库
   (6) 删除远程仓库的文件
       git rm -r --cached filename 删除缓存
       git commit -m "提交信息"
       git push 提交后就会删除远程仓库文件
   

