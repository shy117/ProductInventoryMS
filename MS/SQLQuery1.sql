--�û���
create table Manager
  (Mno int identity(1,1) primary key,
   Mname char(20),
   Maccount char(20) unique not null,
   Mpassword char(20) not null,
   Mrole char(20)
  );

--����
create table Stock
  (Sno int identity(1,1)primary key,
   Sname char(20) not null,
   Scategory char(20),
   Scount int,
   Saddr char(20),
   Smanu char(20),
   Snote char(100),
  );

--����
create table InStock
  (Ino int identity(1,1)primary key ,
   Sno int,
   Sname char(20),
   Icount int,
   Itime datetime,
   Iagent char(20),
   foreign key(Sno) references Stock(Sno)
  );

--�����
create table OutStock
  (Ono int identity(1,1)primary key ,
   Sno int,
   Sname char(20),
   Ocount int,
   Otime datetime,
   Oclient char(20),
   foreign key(Sno) references Stock(Sno)
  );

--����Լ��
alter table Stock add constraint
CK_Scount check(Scount >= 0)

alter table InStock add constraint
CK_Icount check(Icount >= 0)

alter table OutStock add constraint
CK_Ocount check(Ocount >= 0)

--����������ĳ�����
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

---�����������
insert into Manager values('����', '1001', '123456', '��ͨ����Ա'),
						(null,'1002', '123456',null),
						('����', '1003', '123456', 'SuperAdmin'),
						('����', '1004', '123456', 'CommonAdmin')


--


insert into Stock values('���', 'ʳƷ', '1000',null,null,null),
						('�㳦', 'ʳƷ', '10000','�㽭',null,null),
						('����', 'ʳƷ', '5000','�㽭',null,null),
						('����', '�ҵ�', '100','�㽭','����','��'),
						('����', '�ҵ�', '50','�㽭',null,'��'),
						('�·�', '����', '500','����','����',null),
						('����', '����', '100','����','����','����'),
						('�ֻ�', '����', '100','����',null,'ɽկ�ֻ�'),
						('����', '�Ҿ�', '200','����',null,null),
						('����', '�Ҿ�', '300','����',null,null),
						('����', '�Ҿ�', '1000','����',null,null);

insert into OutStock values('1','���', '111',getdate(),'����');
insert into InStock values('9','����', '5',getdate(),'����');
insert into InStock values('5','����', '11',getdate(),'����');
insert into InStock values('4','����', '3',getdate(),'��');
select * from Stock;


insert into OutStock values('1','���', '1000',getdate(),'����');
insert into OutStock values('9','����', '5',getdate(),'����');
insert into OutStock values('5','����', '11',getdate(),'����');
insert into OutStock values('4','����', '3',getdate(),'��');
select * from Stock;

select * from InStock;
select * from OutStock;




  set IDENTITY_INSERT Stock ON

 
  insert into Stock values(5,'22','22',100,'11','11')

  select * from Stock where Sno = '2'

go

