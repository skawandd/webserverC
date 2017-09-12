# Fichier Makefile racine
# Cette variable contient la liste des sous r�pertoires
# pour lesquels il faudra construire un programme.
# Pour l�instant, seul le serveur web est dans la liste.
FOLDERS = webserver
# Indique � make les r�gles qui ne correspondent pas � la cr�ation
# d�un fichier
# make lancera toujours la construction de cette r�gle si elle est
# demand�e, m�me si un fichier/r�pertoire du nom de la cible existe
# On indique ici la r�gle all ainsi que les r�pertoires
. PHONY : all $ ( FOLDERS )
# La r�gle qui sera ex�cut�e si on lance make sans argument
all : $ ( FOLDERS )
# Cette r�gle va lancer make dans le r�pertoire webserver
# option -C de make
webserver :
make -C webserver