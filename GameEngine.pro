TEMPLATE = subdirs

SUBDIRS += \
	Engine \
	Tester

Tester.depends = Engine
