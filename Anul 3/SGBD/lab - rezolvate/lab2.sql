set serveroutput on;
DECLARE
    x NUMBER(1) := 5;
    y x%TYPE := NULL;
BEGIN
IF x <> y THEN
    DBMS_OUTPUT.PUT_LINE ('valoare <> null este = true');
    ELSE
    DBMS_OUTPUT.PUT_LINE ('valoare <> null este != true');
    END IF;
    x := NULL;
    IF x = y THEN
    DBMS_OUTPUT.PUT_LINE ('null = null este = true');
    ELSE
    DBMS_OUTPUT.PUT_LINE ('null = null este != true');
    END IF;
END;
/

declare
    type emp_record is record (
        cod emp_aba.employee_id%type,
        salariu emp_aba.salary%type,
        job emp_aba.job_id%type
    );
    v_ang emp_record;
BEGIN
    BEGIN
        select employee_id, salary, job_id
        into v_ang
        from employees
        where employee_id = 101;
        DBMS_OUTPUT.PUT_LINE ('Angajatul cu codul '|| v_ang.cod ||
        ' si jobul ' || v_ang.job || ' are salariul ' || v_ang.salariu);
    END;
    
    BEGIN
        DELETE FROM emp_aba
        WHERE employee_id=100
        RETURNING employee_id, salary, job_id INTO v_ang;
        DBMS_OUTPUT.PUT_LINE ('Angajatul cu codul '|| v_ang.cod ||
        ' si jobul ' || v_ang.job || ' are salariul ' || v_ang.salariu);
    END;
    ROLLBACK;
    
    begin
        v_ang.cod:=700;
        v_ang.salariu:= 9000;
        v_ang.job := 'SA_MAN';
        DBMS_OUTPUT.PUT_LINE ('Angajatul cu codul '|| v_ang.cod ||
        ' si jobul ' || v_ang.job || ' are salariul ' || v_ang.salariu);
    end;
END;
/

DECLARE
    v_ang1 employees%ROWTYPE;
    v_ang2 employees%ROWTYPE;
BEGIN
    -- sterg angajat 100 si mentin in variabila linia stearsa
    DELETE FROM emp_aba
    WHERE employee_id = 100
    RETURNING employee_id, first_name, last_name, email, phone_number,
    hire_date, job_id, salary, commission_pct, manager_id,
    department_id
    INTO v_ang1;
    
    -- inserez in tabel linia stearsa
    INSERT INTO emp_aba
    VALUES v_ang1;
    
    -- sterg angajat 101
    DELETE FROM emp_aba
    WHERE employee_id = 101;
    
    -- obtin datele din tabelul employees
    SELECT *
    INTO v_ang2
    FROM employees
    WHERE employee_id = 101;
    
    -- inserez o linie oarecare in emp_***
    INSERT INTO emp_aba
    VALUES(1000,'FN','LN','E',null,sysdate, 'AD_VP',1000, null,100,90);
    
    -- modific linia adaugata anterior cu valorile variabilei v_ang2
    UPDATE emp_aba
    SET ROW = v_ang2
    WHERE employee_id = 1000;
END;
/

declare
    type tablou_indexat is table of number index by pls_integer;
    t tablou_indexat;
    contor number(2) := 1;
begin
    for i in 0..9 loop
        t(i) := i;
    end loop;
    DBMS_OUTPUT.PUT_LINE('Tabloul are ' || t.COUNT ||' elemente: ');
    while contor < t.count loop
        t(contor) := null;
        contor := contor + 2;
    end loop;
    DBMS_OUTPUT.PUT_LINE('Tabloul are ' || t.COUNT ||' elemente: ');
    for i in 0..t.count-1 loop
        DBMS_OUTPUT.PUT_LINE(t(i));
    end loop;
    t.delete(t.first);
    t.delete(5,7);
    t.delete(t.last);
    DBMS_OUTPUT.PUT_LINE('Tabloul are ' || t.COUNT ||' elemente: ');
    
    for i in t.first..t.last loop
        if t.exists(i) then
            DBMS_OUTPUT.PUT_LINE(t(i));
        end if;
    end loop;
    
    t.delete;
    DBMS_OUTPUT.PUT_LINE('Tabloul are ' || t.COUNT ||' elemente: ');
end;
/

declare
    type t_ang is table of emp_aba%rowtype index by pls_integer;
    t t_ang;
begin
    delete from emp_aba
    where rownum <= 2
    returning employee_id, first_name, last_name, email, phone_number,
        hire_date, job_id, salary, commission_pct, manager_id,
        department_id
    bulk collect into t;
    
    DBMS_OUTPUT.PUT_LINE (t(1).employee_id ||' ' || t(1).last_name);
    DBMS_OUTPUT.PUT_LINE (t(2).employee_id ||' ' || t(2).last_name);
    
    insert into emp_aba values t(1);
    insert into emp_aba values t(2);
end;
/

declare
    type t_ang is table of number;
    t t_ang := t_ang();
begin
    for i in 0..9 loop
        t.extend;
        t(t.last) := i;
    end loop;
    dbms_output.put_line(t.count);
    for i in t.first..t.last loop
        dbms_output.put(t(i) || ' ');
    end loop;
    dbms_output.new_line;
    for i in t.first..t.last loop
        if i mod 2 = 1 then
            t(i) := null;
        end if;
    end loop;
    dbms_output.put_line(t.count);
    for i in t.first..t.last loop
        dbms_output.put(t(i) || ' ');
    end loop;
    dbms_output.new_line;
    t.delete(t.first);
    t.delete(5, 7);
    t.trim;
    dbms_output.put_line(t.first || ' ' || t(t.first) || ' ' || t.last || ' ' || t(t.last));
    dbms_output.put_line(t.count);
    for i in t.first..t.last loop
        if t.exists(i) then
            dbms_output.put(t(i) || ' ');
        end if;
    end loop;
    dbms_output.new_line;
    t.delete;
    dbms_output.put_line(t.count);
end;
/

declare
    type t_chr is table of char(1);
    t t_chr := t_chr('m', 'i', 'n', 'i', 'm');
begin
    for i in t.first..t.last loop
        dbms_output.put(t(i) || ' ');
    end loop;
    dbms_output.new_line;
    
    for i in t.first..t.last loop
        dbms_output.put(t(t.last-i+t.first) || ' ');
    end loop;
    dbms_output.new_line;
    
    t.delete(2);
    t.delete(4);
    
    dbms_output.put_line(t.count);
    for i in t.first..t.last loop
        if t.exists(i) then
            dbms_output.put(t(i) || ' ');
        end if;
    end loop;
    dbms_output.new_line;
end;
/

DECLARE
TYPE vector IS VARRAY(10) OF NUMBER;
t vector:= vector();
BEGIN
-- punctul a
FOR i IN 1..10 LOOP
t.extend; t(i):=i;
END LOOP;
DBMS_OUTPUT.PUT('Tabloul are ' || t.COUNT ||' elemente: ');
FOR i IN t.FIRST..t.LAST LOOP
DBMS_OUTPUT.PUT(t(i) || ' ');
END LOOP;
DBMS_OUTPUT.NEW_LINE;
-- punctul b
FOR i IN 1..10 LOOP
IF i mod 2 = 1 THEN t(i):=null;
end if;
END LOOP;
DBMS_OUTPUT.PUT('Tabloul are ' || t.COUNT ||' elemente: ');
FOR i IN t.FIRST..t.LAST LOOP
DBMS_OUTPUT.PUT(nvl(t(i), 0) || ' ');
END LOOP;
DBMS_OUTPUT.NEW_LINE;
-- punctul c
-- metodele DELETE(n), DELETE(m,n) nu sunt valabile pentru vectori!!!
-- din vectori nu se pot sterge elemente individuale!!!
-- punctul d
t.delete;
DBMS_OUTPUT.PUT_LINE('Tabloul are ' || t.COUNT ||' elemente.');
END;
/

create or replace type subordonati_aba is varray(10) of number(4);
/
create table manageri_aba (
    cod_mgr number(10),
    nume varchar2(20),
    lista subordonati_aba
);

DECLARE
    v_sub subordonati_aba:= subordonati_aba(100,200,300);
    v_lista manageri_aba.lista%TYPE;
BEGIN
    INSERT INTO manageri_aba
    VALUES (1, 'Mgr 1', v_sub);
    
    INSERT INTO manageri_aba
    VALUES (2, 'Mgr 2', null);
    
    INSERT INTO manageri_aba
    VALUES (3, 'Mgr 3', subordonati_aba(400,500));
    
    SELECT lista
    INTO v_lista
    FROM manageri_aba
    WHERE cod_mgr=1;
    
    FOR j IN v_lista.FIRST..v_lista.LAST loop
        DBMS_OUTPUT.PUT_LINE (v_lista(j));
    END LOOP;
END;
/
SELECT * FROM manageri_aba;
DROP TABLE manageri_aba;
DROP TYPE subordonati_aba;

create table emp_test_aba as (
    select employee_id, last_name
    from employees
);

create or replace type t_telefon is table of varchar2(10);
/

alter table emp_test_aba
add (telefon t_telefon)
nested table telefon store as t_telefon_aba;

insert into emp_test_aba
values (300, 'Banu', t_telefon('0734753638', '1234567890'));

update emp_test_aba
set telefon = t_telefon('0734753638')
where employee_id = 100;

select *
from emp_test_aba;

drop type t_telefon;
drop table emp_test_aba;

declare
    type tip_cod is table of number;
    coduri tip_cod := tip_cod(101, 103, 105);
begin
    forall i in coduri.first..coduri.last
        delete from emp_aba
        where employee_id = coduri(i);
end;
/
select * from emp_aba;
rollback;

create or replace type tip_cod is varray(5) of number;
/
declare
    coduri tip_cod := tip_cod();
    x number;
begin
    select a.employee_id
    bulk collect into coduri
    from (
        select employee_id
        from emp_aba
        where commission_pct is null
        order by salary
    ) a
    where rownum <= 5;
    
    for i in coduri.first..coduri.last loop
        select salary
        into x
        from emp_aba
        where employee_id = coduri(i);
        dbms_output.put(x || ' ');
    end loop;
    dbms_output.new_line;
    
    forall i in coduri.first..coduri.last
        update emp_aba
        set salary = salary * 1.05
        where employee_id = coduri(i);

    for i in coduri.first..coduri.last loop
        select salary
        into x
        from emp_aba
        where employee_id = coduri(i);
        dbms_output.put(x || ' ');
    end loop;
    dbms_output.new_line;
end;
/
drop type tip_cod;

create or replace type tip_orase_aba is table of varchar2(50);
/
create table excursie_aba (
    cod_excursie number(4),
    denumire varchar2(20),
    orase tip_orase_aba,
    status varchar2(20) check(status in ('disponibila', 'anulata'))
)
nested table orase store as tabel_orase_aba;

insert into excursie_aba
values (1, 'sinaia', tip_orase_aba('bucuresti', 'sinaia'), 'disponibila');

insert into excursie_aba
values (2, 'predeal', tip_orase_aba('bucuresti', 'sinaia'), 'anulata');

insert into excursie_aba
values (3, 'azuga', tip_orase_aba('bucuresti', 'azuga'), 'disponibila');

insert into excursie_aba
values (4, 'brasov', tip_orase_aba('bucuresti', 'sinaia'), 'anulata');

insert into excursie_aba
values (5, 'bucuresti', tip_orase_aba('bucuresti', 'sinaia'), 'disponibila');

set verify off;
begin
--    declare
--        v_cod number(4) := &cod;
--        v_oras_ultim varchar2(50) := '&oras_ultim';
--        v_oras_doi varchar2(50) := '&oras_doi';
--        inv1 varchar2(50) := '&inversat_1';
--        inv2 varchar2(50) := '&inversat_2';
--        elim varchar2(50) := '&sterge';
--        v_orase tip_orase_aba;
--        inv1_ind number;
--        inv2_ind number;
--        aux varchar2(50);
--        ind number;
--    begin
--        select orase
--        into v_orase
--        from excursie_aba
--        where cod_excursie = v_cod;
--        
--        v_orase.extend;
--        v_orase(v_orase.last) := v_oras_ultim;
--        
--        v_orase.extend;
--        ind := v_orase.last;
--        while ind > 2 loop
--            v_orase(ind) := v_orase(ind-1);
--            ind := v_orase.prior(ind);
--        end loop;
--        v_orase(2) := v_oras_doi;
--        
--        for i in v_orase.first..v_orase.last loop
--            if v_orase(i) = inv1 then
--                inv1_ind := i;
--            end if;
--            if v_orase(i) = inv2 then
--                inv2_ind := i;
--            end if;
--        end loop;
--        
--        if inv1_ind is not null and inv2_ind is not null then
--            aux := v_orase(inv1_ind);
--            v_orase(inv1_ind) := v_orase(inv2_ind);
--            v_orase(inv2_ind) := aux;
--        end if;
--        
--        for i in v_orase.first..v_orase.last loop
--            if v_orase(i) = elim then
--                v_orase.delete(i);
--                goto iesire;
--            end if;
--        end loop;
--        
--        <<iesire>>
--        update excursie_aba
--        set orase = v_orase
--        where cod_excursie = v_cod;
--    end;
    
--    declare
--        v_cod number(4) := &cod;
--        v_orase tip_orase_aba;
--    begin
--        select orase
--        into v_orase
--        from excursie_aba
--        where cod_excursie = v_cod;
--        
--        dbms_output.put_line(v_orase.count);
--        for i in v_orase.first..v_orase.last loop
--            dbms_output.put(v_orase(i) || ' ');
--        end loop;
--        dbms_output.new_line;
--    end;

--    declare
--        type tabel_orase is table of tip_orase_aba;
--        orase tabel_orase;
--    begin
--        select orase
--        bulk collect into orase
--        from excursie_aba;
--        
--        for i in orase.first..orase.last loop
--            for j in orase(i).first..orase(i).last loop
--                dbms_output.put(orase(i)(j) || ' ');
--            end loop;
--            dbms_output.new_line;
--        end loop;
--    end;

    declare
        type tabel_orase is table of tip_orase_aba;
        orase tabel_orase;
        minim number := 99999999999999;
        t tip_orase_aba;
        type tip_cod is table of number;
        coduri tip_cod;
    begin
        select orase
        bulk collect into orase
        from excursie_aba;
        
        for i in orase.first..orase.last loop
            if orase(i).count < minim then
                minim := orase(i).count;
            end if;
        end loop;
        
        select cod_excursie
        bulk collect into coduri
        from excursie_aba;
        
        for i in coduri.first..coduri.last loop
            select orase
            into t
            from excursie_aba
            where cod_excursie = coduri(i);
            
            if t.count = minim then
                update excursie_aba
                set status = 'anulata'
                where cod_excursie = coduri(i);
            end if;
        end loop;
    end;
end;
/

select * from excursie_aba;