#/bin/bash 
python manage.py makemigrations && python manage.py migrate --run-syncdb && python manage.py collectstatic --no-input  && python manage.py runserver 0.0.0.0:8002 --noreload