set verify off;
set serveroutput on;

create table error_aba (
    cod number,
    mesaj varchar2(100)
);

declare
    v_cod number;
    v_mesaj varchar2(100);
    x number;
    ex exception;
begin
    x := 1;
    if x = 1 then raise ex;
    else x := x / (x-1);
    end if;
exception
    when ex then
        v_cod := -20001;
        v_mesaj := 'x = 1 determina impartire cu 0.';
        insert into error_aba
        values (v_cod, v_mesaj);
end;
/

select * from error_aba;

alter table dept_aba
add constraint c_pr_aba primary key(department_id);

alter table emp_aba
add constraint c_ex_aba foreign key(department_id) references dept_aba(department_id);

delete from dept_aba
where department_id = 10;

declare
    v_cod number := &cod;
    v_nr number;
    exceptie exception;
begin
    select count(*) into v_nr
    from emp_aba
    where department_id = v_cod;
    
    if v_nr != 0 then raise exceptie;
    end if;
    
    delete from dept_aba
    where department_id = v_cod;
exception
    when exceptie then
        dbms_output.put_line('Eroare.');
end;
/

declare
    v_nr number := &x;
    exceptie exception;
    pragma exception_init(exceptie, -06502);
begin
    dbms_output.put_line(sqrt(v_nr));
exception
    when exceptie then
        insert into error_aba
        values (-06502, 'Numar negativ in radical.');
end;
/

select * from error_aba;