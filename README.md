# CS225
<<<<<<< HEAD
=======

 关于之后的任务是否要使用GitHub：
  
  1.最开始的Assignments的代码量可能还没那么大，可能基本用不大到，但是我了解了一下挺多组都会用GitHub的。用微信群确实方便，但之后project任务量大起来的时候，在微信群里上传更新什么的可能会很乱，毕竟微信里保存的文件没有一个很好的框架，找起来可能会有点麻烦。
  
  2.一方面是以后的Project工作量大的时候肯定用Github会清晰方便一点，另外一方面是日后参与什么科研和实习，或者是之后的CS课程，也都会用到GitHub，现在用起来好处还是挺多的
  
  3.虽然刚开始会比较麻烦，但是用多了就熟悉啦！！！
  
———————————————————————分割线———————————————————————

关于GitHub使用和一些注意事项：

###因为我对branch进行了大量的更新，你们首先要做的可能是"git remote show origin"查看一下你们本地和远端的差异：

  0.建议先看后面的”关于branch的操作“再回来继续往下看👇

  1.执行一下"git fetch"，将远端的更新全部取回本地
  
  2.再执行“git remote show origin"查看差异，如果还有不同就继续看后面关于branch的操作，去看下面我发的一个链接文章（主要是我也不是很清楚这时候更新有没有同步。。。。。。）
  
  3.如果这时候你本地有的分支和远端有的分支已经完全相同，但是“Local refs configured for 'git push':”下面的内容中有显示"local out of date"，这表明分支中的内容还没有同步，那么就切换到相应分支执行"git pull“操作进行内容更新，如何切换到相应分支在下面有讲。
  
  4.再执行“git remote show origin"查看差异（大概这时候已经完全相同了吧我希望。。。。）

###每个人的branch里似乎都有个叫“.DS_Store”的二进制文件，貌似是我用我的电脑进行更新操作的时候自动产生的，应该没什么影响

1.当你当前所选择的Branch有内容更新时，你必须先进行git pull操作将本地文件夹更新，才能继续进行git push来上传你的文件。例如：我先更新gyh这个分支里的某个文件，那么另外一个人想要上传文件到gyh，必须先执行git pull来获取我的更新，再进行git push来上传自己的更新，如果不执行git pull而直接执行git push就会有“rejected”报错。而要怎么知道我更新了gyh中的文件呢，我推荐的方法是"git remote show origin"，可以查看远端和本地的各个分支的同步情况；一种方法是我直接告诉你们，另一种方法是我发起pull request让别人知道我更新了文件，最后一种方法是你执行git push发现有报错于是执行git pull。

2.关于pull request的使用还有待研究

3.目前我的想法是每个人有自己的Branch和一个总的main。当有Assignment时，把Assignment的一些文件上传到main中，然后给每个人从main里面获取Assignment文件（这样就避免每个人都要一个一个文件从BlackBoard上下载，我感觉一个个下载好烦），分配任务之后，每个人把自己相应完成的任务上传到自己的Branch里，最后由一个人从每个branch中下载再汇总上传到main中。这样可以避免重复更新main，并且每个人都对自己的branch进行上传更新操作而不需要对其他人的branch进行更新操作，可以避免一些失误。当然这是我的想法，我感觉这样可执行性还可以，大家有什么想法可以说一下。

4.每一次打算上传文件的时候，一定一定先执行git status查看当前所在分支，避免误传

目前就想到这么多，大家以后一起补充吧

———————————————————————分割线———————————————————————

 关于Branch的设立和使用：
 
 1.  "git branch" 查看本地同步的分支，目前远端已经创立好了所有四个分支，我这里本地也已经同步了四个分支。
 
 1-1."git remote show origin"将会查看远端和本地的所有分支以及对应的情况。如果我创建了一个新的分支，你可以通过该命令看到远端有这个分支而你本地没有，你可以执行“git fetch“将分支进行同步。我已经把每个人相对应的分支设立好了，你们就不用再进行创建分支的操作，只需要执行“git fetch"进行一下分支的同步就可以。以后要是会用到再研究。更多详细的操作可以看：https://blog.csdn.net/weixin_44598071/article/details/87818200?utm_medium=distribute.pc_relevant.none-task-blog-BlogCommendFromBaidu-1.control&depth_1-utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromBaidu-1.control
 
 1-2."git pull"将会同步当前分支中的文件到本地
 
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
>>>>>>> 708d9c5dc25db482e98139562b80581ee39a89bb
