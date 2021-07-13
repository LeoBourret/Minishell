"ls>a" a fix
";" a remettre
pipe en cour :
http://www.zeitoun.net/articles/communication-par-tuyau/start
http://www.zeitoun.net/_media/articles/communication-par-tuyau/stdxxx_2.png
http://www.rozmichelle.com/pipes-forks-dups/
https://tldp.org/LDP/lpg/node11.html

tu peux faire un wrapper de fork fork_child(int in, int out, int fd_to_close) qui gere tous les cas de fork a faire (que ca soit pipe ou commande normale)
Pour une commande normale tu fais fork_child(STDIN_FILENO, STDOUT_FILENO, -1 (rien a close))
pour un pipe tu met tes in et out qu'il faut et fd_to_close le fd a close dans le fork (celui du pipe qui sert pas) et tu fais des if (in != STDIN_FILENO) ou (out != STDOUT_FILENO) pour detecter si c'est un cas de pipe ou pas (donc si il faut dup des fd dans le fork ou close des fd dans le fork et le parent apres avoir dup)
la fonction return le pid donc elle s'utilise exactement comme un fork normal sauf que dans le fork tu as les bon fd pour etre pipe
la fonction tiens en 15 lignes apres t'as juste a gerer ta suite de pipe en appelant pipe() une fois par |