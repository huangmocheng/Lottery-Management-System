# Ubuntu22.04下基于C语言的彩票管理系统
    
该系统采用分层模式设计，模拟双色球6+1的玩法，实现管理人员发布彩票，彩民购买彩票，公证员开奖当期彩票，当期彩票开奖后中奖者余额实时更新，需管理人员发布新一期彩票后彩民才能购买新一期彩票，三者均使用同一客户端登录，管理人员与公证员有唯一账号密码，且不可被注册，彩民使用时需注册账号使用。
 
 一、管理员功能:
      1、发行新一期彩票。管理员能够发行某一期彩票（上一期已开奖才可发布下一期）；
      2、显示所有彩票信息。显示目前所有彩票期号、彩票单价、开奖状态、开奖号码、售出总数及奖池金额； 
      3、显示彩民信息。显示当前所有彩民账号、密码、余额及累积中奖金额；
      4、查询彩民信息。管理员能够根据彩民账号或者彩民账户余额区间查找彩民的信息；
      5、排序。管理员能够根据彩民账号或彩民账户余额进行排序显示彩民信息；
      6、增加当前奖池金额。管理员能够增加当前奖池金额；
      7、保存。彩票信息和彩民信息（既能够在内存中存在，也能够存于磁盘中，掉电后信息不丢失）。在内存中，所有彩票的信息以链表的方式存在；在硬盘中，以bat文件格式存在。
        管理员账号：admin        密码：admin

二、公证员功能:
      1、当期彩票随机开奖。开奖后中奖者根据中奖等级实时更新账户余额；
      2、当期彩票指定开奖。指定一组中奖号码作为当期开奖号；
      3、查询某一期彩票中奖信息。通过彩票期号查询所有当期彩票中奖信息，包含彩票期号、单注金额、用户开奖号、购买注数、购买金额、彩民账号及中奖金额；
      4、公证员其余功能与管理员一致。
      公证员账号：notary        密码：notary

三、彩民功能:
      1、查看个人信息。包括账号、密码、账户余额、累积中奖金额等；
      2、查询彩票购买历史。包括彩票信息、中奖信息等；
      3、账户充值。充值金额用于购买彩票；
      4、购买彩票。购买当期彩票，可选择机选号码、手选号码及批量机选；
      5、修改密码。
      6、注销账号。注销当前账户，删除该账号，该账号彩票购买记录仍存在。
