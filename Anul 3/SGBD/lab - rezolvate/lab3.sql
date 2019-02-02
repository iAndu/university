set serveroutput on;

declare
    v_dept varchar2(50);
    v_nr number;
    cursor c is
        select d.department_name, count(*)
        from dept_aba d
        join emp_aba e  on d.department_id = e.department_id
        group by d.department_name;
begin
    open c;
    loop
        fetch c into v_dept, v_nr;
        exit when c%notfound;
        dbms_output.put('In departamentul ' || v_dept || ' ');
        case
            when v_nr = 0 then dbms_output.put_line('nu lucreaza angajati.');
            when v_nr = 1 then dbms_output.put_line('lucreaza un angajat.');
            else dbms_output.put_line('lucreaza ' || v_nr || ' angajati.');
        end case;
    end loop;
    close c;
end;
/

declare
    type r_dept is record (
        v_dept varchar2(50),
        v_nr number
    );
    type tab_dept is table of r_dept;
    v_list tab_dept;
    cursor c is
        select d.department_name, count(e.employee_id)
        from dept_aba d
        left join emp_aba e on d.department_id = e.department_id
        group by d.department_name;
begin
    open c;
    loop
        fetch c bulk collect into v_list limit 5;
        exit when c%notfound;
        for i in v_list.first..v_list.last loop
            dbms_output.put('In departamentul ' || v_list(i).v_dept || ' ');
            case
                when v_list(i).v_nr = 0 then dbms_output.put_line('nu lucreaza angajati.');
                when v_list(i).v_nr = 1 then dbms_output.put_line('lucreaza un angajat.');
                else dbms_output.put_line('lucreaza ' || v_list(i).v_nr || ' angajati.');
            end case;
        end loop;
    end loop;
    close c;
end;
/

declare
    idx number := 0;
    cursor c is
        select e.last_name nume, count(ee.employee_id) nr
        from employees e
        left join employees ee on e.employee_id = ee.manager_id
        group by e.employee_id, e.last_name
        order by nr desc;
begin
    for mng in c loop
        dbms_output.put_line('Managerul ' || mng.nume || ' are ' || mng.nr || ' subordonati.');
        exit when c%rowcount > 4;
    end loop;
end;
/

declare
    v_x number := &x;
    cursor c is
        select d.department_name nume, count(e.employee_id) nr
        from dept_aba d
        left join emp_aba e on d.department_id = e.department_id
        group by d.department_name
        having count(e.employee_id) >= v_x;
begin
    for r in c loop
        dbms_output.put('In departamentul ' || r.nume || ' ');
        case
            when r.nr = 0 then dbms_output.put_line('nu lucreaza angajati.');
            when r.nr = 1 then dbms_output.put_line('lucreaza un angajat.');
            else dbms_output.put_line('lucreaza ' || r.nr || ' angajati.');
        end case;
    end loop;
end;
/

declare
    cursor c is
        select *
        from emp_aba
        where to_char(hire_date, 'yyyy') = 2000
        for update of salary nowait;
begin
    for r in c loop
        update emp_aba
        set salary = salary + 1000
        where current of c;
    end loop;
end;
/

declare
    cursor d is
        select department_id id, department_name nume
        from dept_aba
        where department_id in (10, 20, 30, 40);
        
    cursor e (param number) is
        select last_name nume
        from emp_aba
        where department_id = param;
begin
    for dept in d loop
        dbms_output.put('Departamentul ' || dept.nume || ': ');
        for emp in e(dept.id) loop
            dbms_output.put(emp.nume || ', ');
        end loop;
        dbms_output.new_line;
    end loop;
end;
/

DECLARE
TYPE emp_tip IS REF CURSOR RETURN employees%ROWTYPE;
-- sau
-- TYPE emp_tip IS REF CURSOR;
v_emp emp_tip;
v_optiune NUMBER := &p_optiune;
v_ang employees%ROWTYPE;
BEGIN
IF v_optiune = 1 THEN
OPEN v_emp FOR SELECT *
FROM employees;
ELSIF v_optiune = 2 THEN
OPEN v_emp FOR SELECT *
FROM employees
WHERE salary BETWEEN 10000 AND 20000;
ELSIF v_optiune = 3 THEN
OPEN v_emp FOR SELECT *
FROM employees
WHERE TO_CHAR(hire_date, 'YYYY') = 2000;
ELSE
DBMS_OUTPUT.PUT_LINE('Optiune incorecta');
END IF;
LOOP
FETCH v_emp into v_ang;
EXIT WHEN v_emp%NOTFOUND;
DBMS_OUTPUT.PUT_LINE(v_ang.last_name);
END LOOP;
DBMS_OUTPUT.PUT_LINE('Au fost procesate '||v_emp%ROWCOUNT
|| ' linii');
CLOSE v_emp;
END;
/

DECLARE
    type r_emp is record (
        nume emp_aba.last_name%type,
        salariu emp_aba.salary%type,
        comision emp_aba.commission_pct%type
    );
    TYPE empref IS REF CURSOR;
    v_emp empref;
    v_nr INTEGER := &n;
    v_x r_emp;
BEGIN
    OPEN v_emp FOR
    'SELECT last_name, salary, commission_pct ' ||
    'FROM employees WHERE salary > :bind_var'
    USING v_nr;
    
    loop
        fetch v_emp into v_x;
        exit when v_emp%notfound;
        dbms_output.put(v_x.nume || ' ' || v_x.salariu);
        if v_x.comision is not null then
            dbms_output.put(' ' || v_x.comision);
        end if;
        dbms_output.new_line;
    end loop;
END;
/

set verify off;
declare
    type refcursor is ref cursor;
    job_title jobs.job_title%type;
    cursor c is
        select j.job_title, (
            select count(*)
            from employees
            where job_id = j.job_id
        ) nr_angajati, (
            select sum(salary)
            from employees
            where job_id = j.job_id
        ) venit_lunar, (
            select avg(salary)
            from employees
            where job_id = j.job_id
        ) venit_mediu, cursor (
            select e.last_name, e.salary, rownum
            from (
                select last_name, salary, job_id
                from employees
                order by salary desc
            ) e
            where e.job_id = j.job_id
        )
        from jobs j;
    c_emp refcursor;
    type tip_emp is record (
        last_name employees.last_name%type,
        salary employees.salary%type,
        ord number
    );
    type tip_job is record (
        job_title jobs.job_title%type,
        nr_angajati number,
        venit_lunar employees.salary%type,
        venit_mediu number(8, 2)
    );
    v_job tip_job;
    v_emp tip_emp;
    type tip_total is record (
        angajati number default 0,
        venit_lunar number default 0,
        venit_mediu number default 0
    );
    v_total tip_total;
begin
    open c;
    loop
        fetch c into v_job.job_title, v_job.nr_angajati, v_job.venit_lunar, v_job.venit_mediu, c_emp;
        exit when c%notfound;
        v_total.angajati := v_total.angajati + v_job.nr_angajati;
        v_total.venit_lunar := v_total.venit_lunar + v_job.venit_lunar;
        v_total.venit_mediu := v_total.venit_mediu + v_job.venit_mediu;
        dbms_output.put('Job: ' || v_job.job_title || ', Nr. angajati: ' || v_job.nr_angajati || ', Venit lunar: '
            || v_job.venit_lunar || ', Venit mediu: ' || v_job.venit_mediu || ': ');
        loop
            fetch c_emp into v_emp;
            exit when c_emp%notfound or c_emp%rowcount > 5;
            dbms_output.put(v_emp.ord || '-' || v_emp.last_name || '-' || v_emp.salary || ', ');
        end loop;
        if c_emp%rowcount < 5 then
            dbms_output.put('Sunt mai putin de 5 angajatii.');
        end if;
        dbms_output.new_line;
    end loop;
    close c;
    dbms_output.put_line('Total: ' || v_total.angajati || ' angajati, ' || v_total.venit_lunar || ' venit lunar, '
        || v_total.venit_mediu || ' venit mediu.');
end;
/