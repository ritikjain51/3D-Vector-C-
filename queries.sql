create or replace type name_type is varray(3) of varchar2(20);

create or replace type address_type is varray(3) of varchar2(20);
create or replace type phone_type is varray(2) of number(20);
create or replace type credit_detail_type is varray(3) of varchar2(20);
create sequence cust_inc start with 100000 increment by 1;

create table customer (cust_id number not null, cust_name name_type not null, cust_add address_type not null, phone phone_type not null, profile bfile, email varchar2(30) not null unique, pword varchar2(20) not null, dbirth date, gender varchar2(5), creditcard credit_detail_type, primary key (cust_id));

create trigger cust_id_trigger
	before insert on customer
	for each row 
	begin 
	select cust_inc.nextval
	into :new.cust_id from dual;
end;
/

create table supplier (sup_id number, sup_name name_type not null, sup_add address_type not null, phone phone_type, email varchar2(30) not null unique, dob date, date_join date not null, gender varchar2(6), pword varchar2(20) not null, profile bfile, primary key (sup_id));

create sequence sup_inc start with 1000000 increment by 1;

create trigger sup_id_trigger
	before insert on supplier
	for each row 
	begin 
	select sup_inc.nextval
	into :new.sup_id from dual;
end;
/

create sequence id_inc start with 100000 increment by 1;
create or replace type actors_type is varray(10) of number;
create or replace type lang_type is varray(10) of varchar2(20);

create table movie (id number, 
	m_name varchar2(20) not null unique, 
	sup_id number, 
	add_date date not null, 
	genre varchar2(30) not null, 
	actor_id actors_type, 
	prod_name name_type, 
	dir_name name_type not null, 
	music_com name_type, 
	banner bfile, 
	amtperday number(10,2), 
	length timestamp not null, 
	description varchar2(100), 
	language lang_type, 
	primary key (id),
	foreign key (sup_id) references supplier(sup_id));

create trigger movie_id_inc
	before insert on movie
	for each row 
	begin 
	select id_inc.nextval
	into :new.id from dual;
end;
/


create table actor (actor_id number, act_name name_type not null, actor_rating number not null, industry varchar2(20), dob date, img bfile, primary key(actor_id));

create sequence actor_inc start with 10000 increment by 1;

create trigger actor_id_inc
	before insert on actor
	for each row 
	begin 
	select actor_inc.nextval
	into :new.actor_id from dual;
end;
/

alter table add constraint foreign key (actor_id) references actor (actor_id);

create sequence rating_inc start with 1000 increment by 1;

create table rating (cust_id number not null, 
	movie_id number not null, 
	rating number not null, 
	comments varchar2(100), 
	genre varchar2(20), 
	rate_id number, 
	primary key (rate_id), 
	foreign key (movie_id) references movie(id));

create trigger rate_id_inc
	before insert on rating
	for each row 
	begin 
	select rating_inc.nextval
	into :new.rate_id from dual;
end;
/

create table rent(rent_id number,
	cust_id number not null,
	sup_id number not null, 
	date_of_rent date, 
	noDay number, 
	amount_paid number(10, 2), 
	dateofpayment date, 
	primary key (rent_id),
	foreign key (cust_id) references customer (cust_id),
	foreign key (sup_id) references supplier(sup_id));

create sequence rent_inc start with 10000 increment by 1;

create trigger rent_id_inc
	before insert on rent
	for each row 
	begin 
	select rent_inc.nextval
	into :new.rent_id from dual;
end;
/


create table history (cust_id number, 
	movie_id number, 
	period number, 
	amt_day number(10, 2),
	tax number (10,2),
	date_of_rent number(10,2),
	foreign key (cust_id) references customer(cust_id), 
	foreign key (movie_id) references movie(id));

insert into rating(cust_id, movie_id, rating, comments, genre) values(10000,20000, 5, 'well done ritik', 'thrilling');

insert into customer (cust_id,cust_name, cust_add, phone, email, pword, dbirth, gender, creditcard, ) values (cust_inc.nextval,name_type('Ritik','','Jain'), address_type('KV5, Mansarover', 'Jaipur', '302020'), phone_type(91, 9785225224), 'ritikjain51@gmail.com', 'ritikjain', to_date('22-04-1997', 'dd-mm-yyyy'), 'M', credit_detail_type('5575542000123498', 'Master Card', '01-02-2023'), filename);

insert into supplier (sup_name, sup_add, phone, email, dob, date_join, gender, pword) values(name_type('Anurag','', 'T'), address_type('F170, Swastik Apt', 'Delhi', '110030'), phone_type(91, 9785225224), '14anuragt@gmail.com', to_date('14-06-1995', 'dd-mm-yyyy'), to_date('01-02-2017', 'dd-mm-yyyy'), 'M', 'anuragt');

insert into actor (act_name, actor_rating, industry, dob) values (name_type('Salman', '', 'Khan'), 6, 'bollywood', to_date('01-02-1950', 'dd-mm-yyyy'));

alter table actor add constraint rating_check check (actor_rating >= 1 and actor_rating <= 10);

create table service (movie_id number not null, 
	movie_name varchar2(30), 
	payment_status varchar2(20), 
	cust_id number not null, 
	foreign key (movie_id) references movie(id), 
	foreign key (cust_id) references customer(cust_id), 
	primary key (movie_id, cust_id));

alter table rating add constraint rate_rating_check check (rating >= 1 and rating <= 10);

