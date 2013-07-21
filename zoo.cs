(-W1 -DOS2 -DMSC -DBIG_MEM -DNDEBUG
addfname.c	{options.h various.h zoo.h zoofns.h zooio.h zoomem.h}
basename.c	{assert.h debug.h options.h parse.h various.h zoo.h zoofns.h zooio.h}
comment.c	{errors.i options.h portable.h various.h zoo.h zoofns.h zooio.h}
crcdefs.c	{options.h}
getfile.c	{options.h various.h zoo.h zoofns.h zooio.h zoomem.h}
io.c		{ar.h errors.i lzh.h options.h portable.h zoo.h zooio.h}
machine.c	{options.h various.h zoo.h zoofns.h zooio.h msc.c}
makelist.c	{assert.h debug.h errors.i options.h portable.h various.h zoo.h zoofns.h zooio.h}
misc.c		{errors.i options.h portable.h various.h zoo.h zoofns.h zooio.h}
misc2.c		{errors.i options.h portable.h various.h zoo.h zoofns.h zooio.h zoomem.h}
needed.c	{debug.h options.h portable.h various.h zoo.h zoofns.h zooio.h}
nextfile.c	{options.h various.h zoo.h}
options.c	{errors.i options.h various.h zoo.h zoofns.h zooio.h}
os2.c		{errors.i options.h zoo.h zoofns.h zooio.h}
parse.c		{assert.h options.h parse.h various.h zoo.h zoofns.h zooio.h}
portable.c	{assert.h debug.h machine.h options.h portable.h various.h zoo.h zoofns.h zooio.h}
prterror.c	{options.h various.h zoofns.h zooio.h}
version.c
zoo.c		{errors.i options.h various.h zoo.h zoofns.h zooio.h zoomem.h}
zooadd.c	{debug.h errors.i options.h parse.h portable.h various.h zoo.h zoofns.h zooio.h zoomem.h}
zooadd2.c	{assert.h debug.h errors.i options.h parse.h various.h zoo.h zoofns.h zooio.h}
zoodel.c	{errors.i options.h portable.h various.h zoo.h zoofns.h zooio.h}
zooext.c	{errors.i machine.h options.h parse.h portable.h various.h zoo.h zoofns.h zooio.h}
zoofilt.c	{options.h}
zoolist.c	{errors.i options.h portable.h various.h zoo.h zoofns.h zooio.h zoomem.h}
zoopack.c	{errors.i options.h portable.h various.h zoo.h zoofns.h zooio.h}
)
(-W1 -DOS2 -DMSC -DBIG_MEM -DNDEBUG -Oxaz
addbfmsc.c
decode.c	{ar.h lzh.h options.h zoo.h}
encode.c	{ar.h errors.i lzh.h options.h zoo.h}
huf.c		{ar.h errors.i lzh.h options.h zoo.h}
lzc.c		{assert.h debug.h lzconst.h options.h various.h zoo.h zoofns.h zooio.h zoomem.h}
lzd.c		{assert.h debug.h lzconst.h options.h various.h zoo.h zoofns.h zooio.h zoomem.h}
lzh.c		{ar.h errors.i options.h zoo.h}
maketbl.c	{ar.h lzh.h options.h zoo.h}
maketree.c	{ar.h lzh.h options.h zoo.h}
)
zoo.exe
zoo.def
-AC -LB -S0x8000
