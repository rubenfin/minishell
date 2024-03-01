## Minishell

# Wat moeten we nog doen?
- $? maken ( waarschijnlijk als laatst? ) /builtins/
- libft in Makefile zetten
- echo werkend maken met -n

# Kleine dingen
- als cd path niet juist is /directory of directory juist printen
- cd - fixen
- segfault met spaces en tabs fixen
- cd return value fixen

ls -l | cat -e << eof | ls -l | cat -e, en dan STDIN closen krijg je segfault met fsantiize
echo -na fewwefw
export test="echo hallo" werkt nog niet