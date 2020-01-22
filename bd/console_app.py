import fire
import psycopg2
import locale 
import prettytable

current_password = ""

class Commands:
    def req1(self):
        connection = psycopg2.connect(host = "localhost", dbname = "postgres", user = "postgres", password = current_password)
        command = connection.cursor()
        command.execute("""
           select bstu.abiturients.name as "Имя", bstu.abiturients.surname as "Фамилия", bstu.abiturients.thirdname as "Отчество", sum(exams.points) as "Сумма баллов по всем экзаменам"
           from bstu.abiturients
           join bstu.exams on bstu.exams.abit_id = bstu.abiturients.id
           group by name, surname, thirdname
           order by -sum(exams.points);        
        """,)
        print(prettytable.from_db_cursor(command))
        command.close()
        connection.close()

    def req2(self):
        connection = psycopg2.connect(host = "localhost", dbname = "postgres", user = "postgres", password = current_password)
        command = connection.cursor()
        command.execute("""
            select bstu.abiturients.name as "Имя", bstu.abiturients.surname as "Фамилия", bstu.abiturients.thirdname as "Отчество", bstu.specialities.name as "Направление обучения", bstu.exams.points as "Баллы по информатике"
                from bstu.abiturients
                    join bstu.applications on bstu.applications.abit_id = bstu.abiturients.id
                    join bstu.specialities on bstu.specialities.id = bstu.applications.spec_id
                    join bstu.exams on bstu.exams.abit_id = bstu.abiturients.id
                        where bstu.exams.subject_id = 3 and bstu.specialities.id = 68
            group by bstu.exams.points, bstu.specialities.name, bstu.abiturients.name, bstu.abiturients.surname, bstu.abiturients.thirdname
            order by -bstu.exams.points;
        """,)
        print(prettytable.from_db_cursor(command))
        command.close()
        connection.close()

    def req3(self):
        connection = psycopg2.connect(host = "localhost", dbname = "postgres", user = "postgres", password = current_password)
        command = connection.cursor()
        command.execute("""
            select bstu.abiturients.id as "id", bstu.abiturients.name as "Имя", bstu.abiturients.surname as "Фамилия", bstu.abiturients.thirdname as "Отчество", sum(exams.points) as "Сумма баллов по всем экзаменам", bstu.specialities.name as "Направление подготовки"
            from bstu.abiturients
                join bstu.applications on bstu.applications.abit_id = bstu.abiturients.id
                join bstu.specialities on bstu.applications.spec_id = bstu.specialities.id
                join bstu.exams on bstu.exams.abit_id = bstu.abiturients.id
                    where bstu.applications.is_agreed = True and
                        bstu.applications.original_sertificate = True and
                        bstu.applications.abit_id = bstu.abiturients.id
                    group by bstu.abiturients.id, bstu.abiturients.name, bstu.abiturients.surname, bstu.abiturients.thirdname, bstu.specialities.name having sum(exams.points) > 250
                    order by -sum(exams.points)
            limit 10;
        """,)
        print(prettytable.from_db_cursor(command))
        command.close()
        connection.close()
        
    def req4(self):
        connection = psycopg2.connect(host = "localhost", dbname = "postgres", user = "postgres", password = current_password)
        command = connection.cursor()
        command.execute("""
            select bstu.abiturients.id as "id", bstu.abiturients.name as "Имя", bstu.abiturients.surname as "Фамилия", bstu.abiturients.thirdname as "Отчество"
            from bstu.abiturients
                where dorm_needed = True
            group by bstu.abiturients.id, bstu.abiturients.name, bstu.abiturients.surname, bstu.abiturients.thirdname
            order by bstu.abiturients.id
        """,)
        print(prettytable.from_db_cursor(command))
        command.close()
        connection.close()
    
    def all_abiturients(self):
        connection = psycopg2.connect(host = "localhost", dbname = "postgres", user = "postgres", password = current_password)
        command = connection.cursor()
        command.execute("""
            select * from bstu.abiturients
            order by bstu.abiturients.id
        """,)
        print(prettytable.from_db_cursor(command))
        command.close()
        connection.close()

if __name__ == '__main__':      
    fire.Fire(Commands)