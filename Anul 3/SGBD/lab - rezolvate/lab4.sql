set verify off;

create or replace function emp_salary(emp_name emp_aba.last_name%type) return number is
    salary emp_aba.salary%type;
begin
    select salary into salary
    from emp_aba
    where lower(last_name) = lower(emp_name);
    return salary;
EXCEPTION
    WHEN NO_DATA_FOUND THEN
        RAISE_APPLICATION_ERROR(-20000,
        'Nu exista angajati cu numele dat');
    WHEN TOO_MANY_ROWS THEN
        RAISE_APPLICATION_ERROR(-20001,
        'Exista mai multi angajati cu numele dat');
    WHEN OTHERS THEN
        RAISE_APPLICATION_ERROR(-20002,'Alta eroare!');
end;
/

create or replace procedure p3(p_name emp_aba.last_name%type) is
    v_salary emp_aba.salary%type;
begin
    select salary into v_salary
    from emp_aba
    where lower(last_name) = lower(p_name);
    dbms_output.put_line('Angajatul cu numele ' || p_name || ' are salariul ' || v_salary);
exception
    when others then dbms_output.put_line('A aparut o eroare in procedura.');
end;
/

declare
    v_name emp_aba.last_name%type := '&last_name';
begin
    dbms_output.put_line('Angajatul cu numele ' || v_name || ' are salariul ' || emp_salary(v_name));
    exception
        when others then null;
end;
/

begin
    p3('&last_name');
end;
/

create or replace procedure p5_aba(p_cod in out emp_aba.employee_id%type) is
begin
    select manager_id into p_cod
    from emp_aba
    where employee_id = p_cod;
exception
    when other then dbms_output.put_line('A aparut o eroare.');
end;
/

declare
    v_cod emp_aba.employee_id%type := &cod;
begin
    dbms_output.put('Angajatul cu codul ' || v_cod || ' il are ca manager pe angajatul cu codul ');
    p5_aba(v_cod);
    dbms_output.put_line(v_cod);
end;
/

declare
    nume emp_aba.last_name%type;
    procedure p6_aba(rezultat out emp_aba.last_name%type, comision emp_aba.commission_pct%type := null,
                     cod emp_aba.employee_id%type := null) is
    begin
        if comision is not null then
            select last_name into rezultat
            from emp_aba
            where commission_pct = comision;
            dbms_output.put_line('Angajatul care are comisionul ' || comision || ' are numele ' || rezultat);
        else
            select last_name into rezultat
            from emp_aba
            where employee_id = cod;
            dbms_output.put_line('Angajatul care are codul ' || cod || ' are numele ' || rezultat);
        end if;
    exception
        when others then dbms_output.put_line('A aparut o eroare.');
    end;
begin
    p6_aba(nume, 0.4);
    p6_aba(nume, cod=>200);
end;
/

declare
    medie1 number;
    medie2 number;
    function f7(cod_dpt dept_aba.department_id%type) return number is
        v_medie number := 0;
    begin
        select avg(salary) into v_medie
        from emp_aba
        where department_id = cod_dpt;
        return v_medie;
    exception
        when others then dbms_output.put_line('A aparut o eroare.');
    end;
    
    function f7(cod_dpt dept_aba.department_id%type, cod_job jobs.job_id%type) return number is
        v_medie number := 0;
    begin
        select avg(salary) into v_medie
        from emp_aba
        where department_id = cod_dpt and job_id = cod_job;
        return v_medie;
    exception
        when others then dbms_output.put_line('A aparut o eroare.');
    end;
begin
    medie1:=f7(80);
    DBMS_OUTPUT.PUT_LINE('Media salariilor din departamentul 80'
        || ' este ' || medie1);
    medie2 := f7(80,'SA_MAN');
    DBMS_OUTPUT.PUT_LINE('Media salariilor managerilor din'
        || ' departamentul 80 este ' || medie2);
exception
    when others then null;
end;
/

create or replace function f8_aba(nr number) return number is
begin
    if nr = 0 then
        return 1;
    end if;
    return nr * f8_aba(nr-1);
end;
/

begin
    dbms_output.put_line(f8_aba(5));
end;
/

create or replace function f9_aba return number is
    v_medie number := 0;
begin
    select avg(salary) into v_medie
    from emp_aba;
    return v_medie;
end;
/

declare
    cursor c is (
        select last_name, salary
        from emp_aba
        where salary > f9_aba
    );
begin
    for emp in c loop
        dbms_output.put_line(emp.last_name || ' ' || emp.salary);
    end loop;
end;
/

create table info_aba (
    utlizator varchar2(50),
    data timestamp,
    comanda varchar2(50),
    nr_linii number,
    eroare varchar2(50)
);

create or replace function f9_aba(oras locations.city%type) return number is
    v_rezultat number;
    v_bool number;
begin
    select 1 into v_bool
    from locations
    where lower(city) = lower(oras);
    
    select count(*) into v_rezultat
    from emp_aba e
    join dept_aba d on e.department_id = d.department_id
    join locations l on d.location_id = l.location_id
    where lower(l.city) = lower(oras) and (
        select count(distinct job_id)
        from job_history
        where employee_id = e.employee_id
    ) >= 2;
    return v_rezultat;
exception
    when no_data_found then dbms_output.put_line('Nu a fost gasit orasul.');
    when others then dbms_output.put_line('A aparut o eroare.');
end;
/

begin
    dbms_output.put_line(f9_aba('&locatie'));
exception
    when others then null;
end;
/

create or replace procedure p10_aba(cod_manager emp_aba.manager_id%type) is
    type tip_cod is table of emp_aba.employee_id%type;
    coduri tip_cod;
    v_bool number;
begin
    select 1 into v_bool
    from emp_aba
    where employee_id = cod_manager;
    
    select employee_id
    bulk collect into coduri
    from emp_aba
    where manager_id = cod_manager;
    
    if coduri.count != 0 then
        for i in coduri.first..coduri.last loop
            update emp_aba
            set salary = salary * 1.1
            where employee_id = coduri(i);
            p10_aba(coduri(i));
        end loop;
    end if;
exception
    when no_data_found then dbms_output.put_line('Nu exista acest angajat.');
    when others then dbms_output.put_line('Alta eroare.' || cod_manager);
end;
/

select salary
from emp_aba;

begin
    p10_aba(300);
end;
/

declare
    function get_cod(nume_dep dept_aba.department_name%type) return number is
        rezultat number;
    begin
        select department_id into rezultat
        from dept_aba
        where department_name = nume_dep;
        return rezultat;
    end;
    
    function max_employment(cod_dep dept_aba.department_id%type) return number is
        rezultat number;
    begin
        select max(count(*)) into rezultat
        from emp_aba
        where department_id = cod_dep
        group by to_char(hire_date, 'day');
        return rezultat;
    exception
        when no_data_found then return -1;
    end;
    
    function day_max_employment(cod_dep dept_aba.department_id%type) return varchar2 is
        v_max number;
        rezultat varchar2(10);
    begin
        v_max := max_employment(cod_dep);
        select e.d into rezultat
        from (
            select to_char(ee.hire_date, 'day') as d
            from emp_aba ee
            where ee.department_id = cod_dep
            group by to_char(ee.hire_date, 'day')
            having count(*) = v_max
        ) e
        where rownum = 1;
        return rezultat;
    exception
        when no_data_found then return null;
    end;
    
    procedure show_emp(nume_dept dept_aba.department_name%type) is
        counter number := 0;
        v_cod dept_aba.department_id%type;
        v_day varchar2(10);
        cursor c (dep dept_aba.department_id%type, d varchar2) is (
            select last_name, round(sysdate-hire_date) as vechime, salary
            from emp_aba
            where department_id = dep and to_char(hire_date, 'day') = d
        );
    begin
        v_cod := get_cod(nume_dept);
        v_day := day_max_employment(v_cod);
        dbms_output.put(nume_dept || ' ');
        
        if v_day is null then
            dbms_output.put_line('Nu exista angajati.');
        else
            dbms_output.put(v_day || ': ');
            for emp in c(v_cod, v_day) loop
                counter := counter + 1;
                dbms_output.put(emp.last_name || ' ' || emp.vechime || ' ' || emp.salary || ', ');
            end loop;
            dbms_output.new_line;
        end if;
    end;
begin
    for dep in (select department_name from dept_aba) loop
        show_emp(dep.department_name);
    end loop;
end;
/