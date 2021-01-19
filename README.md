# CS225

 关于之后的任务是否要使用GitHub：
  
  1.最开始的Assignments的代码量可能还没那么大，可能基本用不大到，但是我了解了一下挺多组都会用GitHub的。yi fang m



 关于Branch的设立和使用：
 
 1.  "git branch" 查看本地同步的分支，现在有FGSJ、gyh、lhn三个branch
 
 1-1 "git pull"将会同步当前分支中的文件到本地
 
 2.  "git branch name"创建分支。如：当前位于main，执行git branch test会在main中创建test分支
 
 3. "git checkout name" 切换分支。如：git checkout FGSJ切换到FGSJ分支
 
 3-1.切换分支之后会自动将分支中的文件同步到当前本地文件夹
 
 4. 切换分支之后进行add, push等操作会把文件上传到相应分支


———————————————————————分割线———————————————————————

关于本地的设立：

echo "# CS225" >> README.md

git init

git add README.md

git commit -m "first commit"

git branch -M main

git remote add origin https://github.com/Geyuhao/CS225.git

git push -u origin main

###在命令行一步步输####
