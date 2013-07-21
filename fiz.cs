(-W1 -DOS2 -DMSC -DBIG_MEM -DNDEBUG
addbfmsc.c
crcdefs.c	{options.h}
fiz.c		{options.h portable.h various.h zoo.h zoofns.h zooio.h}
portable.c	{assert.h debug.h machine.h options.h portable.h various.h zoo.h zoofns.h zooio.h}
)
fiz.exe
fiz.def
-AC -LB -S0x8000
