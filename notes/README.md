# COOP
obtention de rip OK
creation des objects dans la pile OK
trigger execution de la main loop sur les bons objet NOK
script pour rentrer directement dans le debug gdb NOK


donc pour que l'attaque soit possible peut importe le programme il faut 4 choses :

un buffer ecrivable dnas la heap(pas une vuln ca peut etre amnené ded manière tout a fait classique)
un leak de la heap (vuln: format_string fsop, uaf, doublefree, misuse de la heap)
un leak des vtables (vuln: format_string, fsop, uaf, doublefree, misuse de la heap)
un moyen davoir la main sur rdi et rdx(pas forcement une vuln, suivant les objetc legit quon peut avoir dans
                                       la heap)
un moyen de recuperer la mainnsur rip forcement(vuln: bof, fsop, format_string, uaf, misuse heap)

à faire: un nouveau prog qui fait un switch et des allocation heap comme sur les challs de heap
