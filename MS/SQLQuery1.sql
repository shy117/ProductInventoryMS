--用户表
create table Manager
  (Mno int identity(1,1) primary key,
   Mname char(20),
   Maccount char(20) unique not null,
   Mpassword char(20) not null,
   Mrole char(20)
  );

--库存表
create table Stock
  (Sno int identity(1,1)primary key,
   Sname char(20) not null,
   Scategory char(20),
   Scount int,
   Saddr char(20),
   Smanu char(20),
   Snote char(100),
  );

--入库表
create table InStock
  (Ino int identity(1,1)primary key ,
   Sno int,
   Sname char(20),
   Icount int,
   Itime datetime,
   Iagent char(20),
   foreign key(Sno) references Stock(Sno)
  );

--出库表
create table OutStock
  (Ono int identity(1,1)primary key ,
   Sno int,
   Sname char(20),
   Ocount int,
   Otime datetime,
   Oclient char(20),
   foreign key(Sno) references Stock(Sno)
  );

--创建约束
alter table Stock add constraint
CK_Scount check(Scount >= 0)

alter table InStock add constraint
CK_Icount check(Icount >= 0)

alter table OutStock add constraint
CK_Ocount check(Ocount >= 0)

--创建入库出库的出发器
go
create trigger InUpdateStock
on InStock
for insert
as
begin 
  update Stock 
  set Stock.Scount=Stock.Scount+(select Icount from inserted)
  where Stock.Sno in (select Sno from inserted )
end 

go

create trigger OutUpdateStock
on OutStock
for insert
as
begin 
  update Stock 
  set Stock.Scount=Stock.Scount-(select Ocount from inserted)
  where Stock.Sno in (select Sno from inserted )
end 

go
create trigger InUpdateIcount
on InStock
for update
as if update(Icount)
begin 
  update Stock set Stock.Scount=Stock.Scount+(select Icount from inserted)
  where Stock.Sno in (select Sno from inserted )
  update Stock set Stock.Scount=Stock.Scount-(select Icount from deleted)
  where Stock.Sno in (select Sno from deleted )
end 

go
create trigger OutUpdateOcount
on OutStock
for update
as if update(Ocount)
begin 
  update Stock set Stock.Scount=Stock.Scount+(select Ocount from deleted)
  where Stock.Sno in (select Sno from deleted )
  update Stock set Stock.Scount=Stock.Scount-(select Ocount from inserted)
  where Stock.Sno in (select Sno from inserted )
end 

---插入测试数据
insert into Manager values('张三', '1001', '123456', '普通管理员'),
						(null,'1002', '123456',null),
						('李四', '1003', '123456', 'SuperAdmin'),
						('张三', '1004', '123456', 'CommonAdmin')


--


insert into Stock values('面包', '食品', '1000',null,null,null),
						('香肠', '食品', '10000','浙江',null,null),
						('泡面', '食品', '5000','浙江',null,null),
						('电视', '家电', '100','浙江','张三','无'),
						('冰箱', '家电', '50','浙江',null,'无'),
						('衣服', '服饰', '500','重庆','王五',null),
						('电脑', '数码', '100','北京','李四','杂牌'),
						('手机', '数码', '100','深圳',null,'山寨手机'),
						('椅子', '家具', '200','其他',null,null),
						('桌子', '家具', '300','其他',null,null),
						('箱子', '家具', '1000','其他',null,null);

insert into OutStock values('1','面包', '111',getdate(),'李四');
insert into InStock values('9','椅子', '5',getdate(),'张三');
insert into InStock values('5','冰箱', '11',getdate(),'王五');
insert into InStock values('4','电视', '3',getdate(),'无');
select * from Stock;


insert into OutStock values('1','面包', '1000',getdate(),'李四');
insert into OutStock values('9','椅子', '5',getdate(),'张三');
insert into OutStock values('5','冰箱', '11',getdate(),'王五');
insert into OutStock values('4','电视', '3',getdate(),'无');
select * from Stock;

select * from InStock;
select * from OutStock;




  set IDENTITY_INSERT Stock ON

 
  insert into Stock values(5,'22','22',100,'11','11')

  select * from Stock where Sno = '2'

go

