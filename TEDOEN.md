## Minishell

# Wat moeten we nog doen?
- $? maken ( waarschijnlijk als laatst? ) /builtins/
- libft in Makefile zetten

# Kleine dingen
- als cd path niet juist is /directory of directory juist printen
- segfault met spaces en tabs fixen
- cd return value fixen

ls -l | cat -e << eof | ls -l | cat -e, en dan STDIN closen krijg je segfault met fsantiize
echo -na fewwefw
export test="echo hallo" werkt nog niet
lege commands geven nog segfault, en lege pipes daarom ook sgfault in child bijvoorbeeld e| |e

flikker opendir derin /home/rfinneru/Codam/rank03/minishell
i -= x;efw$PAT $hHOMEH $Pwd
LeakSanitizer:DEADLYSIGNAL
==2100431==ERROR: LeakSanitizer: SEGV on unknown address 0x000000000000 (pc 0x000000431bc6 bp 0x7ffd9e6a1ba0 sp 0x7ffd9e6a1b60 T0)
==2100431==The signal is caused by a READ memory access.
==2100431==Hint: address points to the zero page.
    #0 0x431bc6 in ft_strjoin (/home/rfinneru/Codam/rank03/minishell/minishell+0x431bc6)
    #1 0x42fcfa in expanding /home/rfinneru/Codam/rank03/minishell/src/parsing/parsing.c:144:12
    #2 0x42ff05 in set_node /home/rfinneru/Codam/rank03/minishell/src/parsing/parsing.c:193:13
    #3 0x4303f4 in init_redirections /home/rfinneru/Codam/rank03/minishell/src/parsing/parsing.c:296:3
    #4 0x42bf50 in init_command_line /home/rfinneru/Codam/rank03/minishell/src/minishell.c:113:6
    #5 0x42c06d in command_line /home/rfinneru/Codam/rank03/minishell/src/minishell.c:153:16
    #6 0x42ba5f in minishell /home/rfinneru/Codam/rank03/minishell/src/main.c:30:12
    #7 0x42bb51 in main /home/rfinneru/Codam/rank03/minishell/src/main.c:56:12
    #8 0x7fb16ed5ed8f in __libc_start_call_main csu/../sysdeps/nptl/libc_start_call_main.h:58:16
    #9 0x7fb16ed5ee3f in __libc_start_main csu/../csu/libc-start.c:392:3
    #10 0x406494 in _start (/home/rfinneru