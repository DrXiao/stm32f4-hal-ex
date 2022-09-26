
if [ $# -lt 1 ]; then
        echo "usage: ./build.sh [--rtos] <new project name>"
        exit 1
fi

template="stm-template"
project_name=""

if [ $# -eq 1 ]; then
	project_name=$1
else
	if [ $1 == "--rtos" ]; then
		template="rtos-template"
		project_name=$2
	else	
		echo "paramter error: $1"
        	echo "usage: ./build.sh [--rtos] <new project name>"
	        exit 1
	fi
fi

mkdir $project_name
rsync -a $template/ $project_name/