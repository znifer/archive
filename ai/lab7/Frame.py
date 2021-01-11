class Frame:
    def __init__(self):
        self.attrs = []
        self.name = "Фрейм"

    def get_attr(self, name):
        for a in self.attrs:
            if a[1].lower() == name.lower():
                return a[0]
        return None

    def get_value(self, name):
        attr = self.get_attr(name)
        return getattr(self, attr)