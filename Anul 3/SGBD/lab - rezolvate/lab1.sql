set serveroutput on;

<<principal>>
DECLARE
v_client_id NUMBER(4):= 1600;
v_client_nume VARCHAR2(50):= 'N1';
v_nou_client_id NUMBER(3):= 500;
BEGIN
    <<secundar>>
    DECLARE
    v_client_id NUMBER(4) := 0;
    v_client_nume VARCHAR2(50) := 'N2';
    v_nou_client_id NUMBER(3) := 300;
    v_nou_client_nume VARCHAR2(50) := 'N3';
    BEGIN
        v_client_id:= v_nou_client_id;
        principal.v_client_nume:=
        v_client_nume ||' '|| v_nou_client_nume;
        dbms_output.put_line(v_client_id);
        dbms_output.put_line(v_client_nume);
        dbms_output.put_line(v_nou_client_id);
        dbms_output.put_line(v_nou_client_nume);
    END;
    v_client_id:= (v_client_id *12)/10;
    dbms_output.put_line(v_client_id);
    dbms_output.put_line(v_client_nume);
END;
/

VARIABLE g_mesaj VARCHAR2(50);
BEGIN
    :g_mesaj := 'Invat PL/SQL';
END;
/
PRINT g_mesaj

BEGIN
DBMS_OUTPUT.PUT_LINE('Invat PL/SQL');
END;
/

DECLARE
v_dep departments.department_name%TYPE;
v_nr_angajati number(3);
BEGIN
SELECT department_name, count(*)
INTO v_dep, v_nr_angajati
FROM employees e, departments d
WHERE e.department_id=d.department_id
GROUP BY department_name
HAVING COUNT(*) = (SELECT MAX(COUNT(*))
FROM employees

GROUP BY department_id);
DBMS_OUTPUT.PUT_LINE('Departamentul '|| v_dep || ' cu ' || v_nr_angajati || ' de angajati.');
END;
/

VARIABLE rezultat VARCHAR2(35)
BEGIN
SELECT department_name
INTO :rezultat
FROM employees e, departments d
WHERE e.department_id=d.department_id
GROUP BY department_name
HAVING COUNT(*) = (SELECT MAX(COUNT(*))
FROM employees

GROUP BY department_id);

DBMS_OUTPUT.PUT_LINE('Departamentul '|| :rezultat);
END;
/
PRINT rezultat

set verify off;
declare
v_id employees.employee_id%type := &id;
v_salar employees.salary%type;
v_bonus number(4);
begin
    select salary
    into v_salar
    from employees
    where employee_id = v_id;
    
    /*if v_salar > 20000 then
        v_bonus := 2000;
    elsif v_salar > 10000 then
        v_bonus := 1000;
    else
        v_bonus := 500;
    end if;*/
    
    case
        when v_salar > 20000 then v_bonus := 2000;
        when v_salar > 10000 and v_salar <= 20000 then v_bonus := 1000;
        when v_salar <= 10000 then v_bonus := 500;
    end case;
    dbms_output.put_line(v_bonus);
end;
/


set verify off;
define p_emp_id = 200;
define p_dep_id = 80;
define p_proc = 20;
declare
    v_emp_id emp_aba.employee_id%type := &p_emp_id;
    v_dep_id dept_aba.department_id%type := &p_dep_id;
    v_proc number(3) := &p_proc;
begin
    update emp_aba
    set department_id = v_dep_id, salary = salary * (100+v_proc)
    where employee_id = v_emp_id;
    if sql%rowcount = 0 then
        dbms_output.put_line('Nu exista nici un angajat cu acest cod.');
    else
        dbms_output.put_line('Actualizare realizata.');
    end if;
    rollback;
end;
/

create table zile_aba(
    id number(6, 0),
    data date,
    nume_zi varchar(50)
);

declare
    contor number(2) := 1;
    v_data date;
    maxim number(2) := last_day(sysdate) - sysdate;
begin
    loop
        exit when contor > maxim;
        v_data := sysdate + contor;
        insert into zile_aba
        values (contor, v_data, to_char(v_data, 'Day'));
        contor := contor + 1;
    end loop;
end;
/

declare
    contor number(2) := 1;
    v_data date;
    maxim number(2) := last_day(sysdate) - sysdate;
begin
    while contor <= maxim loop
        v_data := sysdate + contor;
        insert into zile_aba
        values (contor, v_data, to_char(v_data, 'Day'));
        contor := contor + 1;
    end loop;
end;
/

declare
    v_data date;
    maxim number(2) := last_day(sysdate) - sysdate;
begin
    rollback;
    for contor in 1..maxim loop
        v_data := sysdate + contor;
        insert into zile_aba
        values (contor, v_data, to_char(v_data, 'Day'));
    end loop;
end;
/

declare
    i positive := 1;
    max_loop constant positive := 10;
begin
    loop
        i := i + 1;
        dbms_output.put_line('In loop: ' || i);
        if i > max_loop then
            goto eticheta;
        end if;
    end loop;
    <<eticheta>>
    i := 1;
    dbms_output.put_line('In afara loop-ului: ' || i);
end;
/

DECLARE
numar number(3):=100;
mesaj1 varchar2(255):='text 1';
mesaj2 varchar2(255):='text 2';
BEGIN
DECLARE
numar number(3):=1;
mesaj1 varchar2(255):='text 2';
mesaj2 varchar2(255):='text 3';
BEGIN
numar:=numar+1;
mesaj2:=mesaj2||' adaugat in sub-bloc';
dbms_output.put_line(numar);
dbms_output.put_line(mesaj1);
dbms_output.put_line(mesaj2);
END;
numar:=numar+1;
mesaj1:=mesaj1||' adaugat un blocul principal';
mesaj2:=mesaj2||' adaugat in blocul principal';
dbms_output.put_line(numar);
dbms_output.put_line(mesaj1);
dbms_output.put_line(mesaj2);
END;
/

set verify off;
declare
    nume_membru varchar2(51);
    cod_membru member.member_id%type;
    titluri number(6);
    total number(6);
begin
    nume_membru := '&nume';
    
    select member_id
    into cod_membru
    from member
    where lower(last_name) = lower(nume_membru);
    
    if sql%rowcount = 0 then
        dbms_output.put_line('Nu exista acest membru.');
        goto iesire;
    elsif sql%rowcount > 1 then
        dbms_output.put_line('Exista mai multe persoane cu acelasi nume.');
        goto iesire;
    end if;
    
    select count(*)
    into titluri
    from reservation
    where member_id = cod_membru;
    dbms_output.put_line(titluri);
    
    select count(*)
    into total
    from reservation;
    
    case
        when titluri / total > 0.75 then dbms_output.put_line('Categoria 1');
        when titluri / total > 0.5 then dbms_output.put_line('Categoria 2');
        when titluri / total > 0.25 then dbms_output.put_line('Categoria 3');
        else dbms_output.put_line('Categoria 4');
    end case;
    
    <<iesire>>
    null;
end;
/

create table member_aba as (
    select *
    from member
);

alter table member_aba
add discount number(3);

declare
    total number(6);
begin
    select count(*)
    into total
    from reservation;
    
    update member_aba m
    set discount = case 
        when (
            select count(*)
            from member_aba mm
            where m.member_id = mm.member_id
        ) / total > 0.75 then 10
        when (
            select count(*)
            from member_aba mm
            where m.member_id = mm.member_id
        ) / total > 0.5 then 5
        when (
            select count(*)
            from member_aba mm
            where m.member_id = mm.member_id
        ) / total > 0.25 then 3
        else 0
    end;
end;
/

declare
    cod_membru member_aba.member_id%type;
    d member_aba.discount%type;
begin
    cod_membru := &cod;
    d := &discount;
    
    update member_aba
    set discount = d
    where member_id = cod_membru;
    
    if sql%rowcount = 0 then
        dbms_output.put_line('Nu exista.');
    else
        dbms_output.put_line('Succes.');
    end if;
end;
/