def search_key(dictionary, search_value):
    for key, value in dictionary.items():  # for name, age in dictionary.iteritems():  (for Python 2.x)
        if value.lower() == search_value.lower():
            return key
