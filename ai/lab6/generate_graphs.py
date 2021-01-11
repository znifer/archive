from knowledge.dictionary1 import dictionary as dictionary1
from knowledge.dictionary2 import dictionary as dictionary2
#from knowledge.dictionary3 import dictionary as dictionary3
from service.plot_network import render

# task1
render('knowledge/task1.pl', dictionary1, 'graph1')
# task2
render('knowledge/task2.pl', dictionary2, 'graph2')
# task3
# render('knowledge/task3.pl', dictionary3, 'graph3')
