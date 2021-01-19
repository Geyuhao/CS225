# CS225

 关于之后的任务是否要使用GitHub：
  
  1.最开始的Assignments的代码量可能还没那么大，可能基本用不大到，但是我了解了一下挺多组都会用GitHub的。用微信群确实方便，但之后project任务量大起来的时候，在微信群里上传更新什么的可能会很乱，毕竟微信里保存的文件没有一个很好的框架，找起来可能会有点麻烦。
  
  2.一方面是以后的Project工作量大的时候肯定用Github会清晰方便一点，另外一方面是日后参与什么科研和实习，或者是之后的CS课程，也都会用到GitHub，现在用起来好处还是挺多的
  
  3.虽然刚开始会比较麻烦，但是用多了就熟悉啦！！！
  
———————————————————————分割线———————————————————————

关于GitHub使用和一些注意事项：

###先执行一下git pull看看有没有更新

###每个人的branch里似乎都有个叫“.DS_Store”的二进制文件，貌似是我用我的电脑进行更新操作的时候自动产生的，应该没什么影响

1.当你当前所选择的Branch有内容更新时，你必须先进行git pull操作将本地文件夹更新，才能继续进行git push来上传你的文件。例如：我先更新gyh里的某个文件，那么另外一个人想要上传文件到gyh，必须先执行git pull来获取我的更新，再进行git push来上传自己的更新，如果不执行git pull而直接执行git push就会有“rejected”报错。而要怎么知道我更新了gyh中的文件呢，一种方法是我直接告诉你们，另一种方法是我发起pull request让别人知道我更新了文件，最后一种方法是你执行git push发现有报错于是执行git pull。

2.关于pull request的使用还有待研究

3.目前我的想法是每个人有自己的Branch和一个总的main。当有Assignment时，把Assignment的一些文件上传到main中，然后给每个人从main里面获取Assignment文件（这样就避免每个人都要一个一个文件从BlackBoard上下载，我感觉一个个下载好烦），分配任务之后，每个人把自己相应完成的任务上传到自己的Branch里，最后由一个人从每个branch中下载再汇总上传到main中。这样可以避免重复更新main，并且每个人都对自己的branch进行上传更新操作而不需要对其他人的branch进行更新操作，可以避免一些失误。当然这是我的想法，我感觉这样可执行性还可以，大家有什么想法可以说一下。

4.每一次打算上传文件的时候，一定一定先执行git status查看当前所在分支，避免误传

目前就想到这么多，大家以后一起补充吧

———————————————————————分割线———————————————————————

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
