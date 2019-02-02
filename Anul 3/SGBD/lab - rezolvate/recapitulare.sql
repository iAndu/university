comment on table emp_aba is 'Informatii despre angajati';

select * from user_tab_comments where table_name = 'EMP_ABA';

alter session set nls_date_format = 'dd.mm.yyyy hh:mi:ss';

select sysdate from dual;

select extract(year from sysdate) from dual;

select extract(month from sysdate), extract(day from sysdate) from dual;

select table_name from user_tables where table_name like '%\____' escape '\';