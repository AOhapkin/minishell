# minishell

## Общие инструкции

- [ ] Проект должен быть написан на Си с соблюдением `norminette`.
- [ ] Функции не должны завершаться неожиданно (segmentation fault, bus error,
  double free и т.д.) за исключением неопределенного поведения.
- [ ] Утечки памяти не допускаются.
- [ ] `Makefile` должен как минимум содержать правила `$(NAME)`, `all`, `clean`
  , `fclean` и `re`.

- [ ] Название программы: `minishell`
- [ ] Разрешенные файлы: Makefile, *.h, *.c
- [ ] Makefile: NAME, all, clean, fclean, re
- [ ] Разрешенные функции:
    - readline, rl_clear_history, rl_on_new_line,
    - rl_replace_line, rl_redisplay, add_history,
    - printf, malloc, free, write, access, open, read,
    - close, fork, wait, waitpid, wait3, wait4, signal,
    - sigaction, sigemptyset, sigaddset, kill, exit,
    - getcwd, chdir, stat, lstat, fstat, unlink, execve,
    - dup, dup2, pipe, opendir, readdir, closedir,
    - strerror, perror, isatty, ttyname, ttyslot, ioctl,
    - getenv, tcsetattr, tcgetattr, tgetent, tgetflag,
    - tgetnum, tgetstr, tgoto, tputs
- [ ] Использование `libft` разрешено

## Minishell должен уметь:

- [x] Показывать `prompt`, когда ждет новую команду.
- [x] Иметь историю работы.
    - [x] Сохраняет прошлые вводы в рамках одной сессии.
    - [x] Можно проверить с помощью стрелок вверх или вниз.
    - [x] Реализовано с помощью
      функции [add_history](https://tiswww.case.edu/php/chet/readline/history.html#:~:text=Function%3A%20void-,add_history,-(const%20char%20*string)
- [ ] Находить и запускать исполняемый файл (на основе PATH или с использованием
  относительного или абсолютного пути).
- [ ] Не использовать более одной глобальной переменной.
- [x] Не интерпретировать незакрытые кавычки, которые не требуются субъекту,
  такому как `\` или `;`.
- [x] Обрабатывать одинарную кавычку `'`, которая должна препятствовать
  интерпретации оболочкой метасимволов в кавычках.
- [x] Обрабатывать двойные кавычки `"`, которые должны препятствовать
  интерпретации оболочкой метасимволов в последовательности в кавычках за
  исключением знака `$`.
- [ ] Операторы перенаправления вывода
    - [ ] Реализовать пайпы (символ `|`). Вывод каждой команды соединяется со
      входом следующей команды через пайп.
        - `echo 'Строка с числом 901255323' | grep -E -o '[0-9]+'`
        - `grep -E -o '[0-9]+' 'Строка с числом 901255323'`
            - вернет `901255323`
    - [ ] `>` перенаправляет вывод в файл.
        - перезаписывает содержимое файла
        - `echo "hello" > one.txt > two.txt > three.txt`
            - создаст все файлы если их нет `one.txt`, `two.txt`, `three.txt`
            - запишет только в `three.txt`
        - `> /dev/null`
            - частный случай вывод **никуда не сохраняется**
    - [ ] `>>` должен перенаправлять вывод в режиме добавления.
        - аналогичен `>` не удаляет содержимое файла, а дописывает новые данные
          к уже существующим.
    - [ ] `<` перенаправляет input.
        - следующий после `<` токен будет считаться именем файла как источником
          ввода вместо клавиатуры
        - команды ниже эквивалентны
            - `КОМАНДА1 < ФАЙЛ1`
            - `cat ФАЙЛ1 | КОМАНДА1`
    - [ ] `<<` следует указать разделитель, а затем читать ввод, пока не будет
      видна строка, содержащая разделитель. Он не должен обновлять историю!
        - дописывает данные в конец файла.
- [ ] Обрабатывать переменны окружения (`$`, за которым последовательность
  символов), которые дожлны расширяться до их значения.
- [x] Handle $? which should expand to the exit status of the most recently
  executed foreground pipeline.
- [ ] Обрабатывать `ctrl-C`, `ctrl-D` и `ctrl-\`, которые ведут себя аналогично
  с bash.
- [ ] В интерактивном (диалоговом) режиме:
    - [ ] `ctrl-C` показывает новый prompt на новой строке.
    - [ ] `ctrl-D` выходит из оболочки.
    - [ ] `ctrl-\` ничего не делает.
- [ ] В оболочке должны быть реализованы встроенные функции:
    - [x] `echo` с флагом `-n` (вывод без переноса строки в конце).
        - вывод всего что после `ehcho`
    - [ ] `cd` только с относительным или с абсолютным путем.
        - перемещение по файловой системе
    - [x] `pwd` без флагов.
        - абсолютный путь текущей директории
    - [x] `export` без флагов.
        - `$ export name=student` передает переменную "name" со значением "
          student":
    - [x] `unset` без флагов.
        -
        противоположность `export` ([статья с примерами](https://www.cyberciti.biz/faq/linux-osx-bsd-unix-bash-undefine-environment-variable/))
    - [x] `env` без флагов или аргументов.
        - выводит список переменных окружения
    - [x] `exit` без флагов.

Функция `readline()` может вызвать утечки памяти. Их не нужно исправлять.

# Minishell прогресс:

- [x] Запускается с помощью `CMake` и показывает `prompt`.
    - [x] Сконфигурировал `CMake` файл чтобы запускалось с
      библиотекой `readline`
        - [инструкция](https://youtrack.jetbrains.com/issue/CPP-12828/CMake-Readline-Support)
    - [x] Минимальный `.h` и `main.c`
    - [x] Лексер
        - делит `prompt` на токены с учетом:
            - `"`, `'` кавычек
            - `\`, `;` не интерпретируемых символов
            - `$` переменных окружения
    - Операции:
        - **export**
            - допустимые аргументы для этой операции
                - [ ] `XPC_FLAGS=0x0`
                - [ ] `XPC_FLAGS=`
                - [ ] `XPC_FLAGS` - **env** такой параметр не покажет!
        - **env**
        - **cd**
            - перейти в директорию
                - `char *getcwd(char *buffer, size_t size);`
                - `int chdir(const char *path);` - смена текущей рабочей
                  директории
            - как это влияет на input/output (< > >>)
            - pipe
            - [x] "cd", когда PWD не существует в env
                - [x] после cd в OLDPWD = ""
                - [x] новая переменная PWD не появляется
            - [x] когда не существует OLDPWD
                - [x] не появляется после выполнения cd
            - не существуют PWD и OLDPWD
                - переменные не появляются после выполнения cd
            - [x] если удалить HOME, команда cd без пути не работает
                - `-bash: cd: HOME not set`
                
# Чек-лист для защиты 

- [ ] Основная часть
  - [x] Простые команды и глобальные переменные
    - [x] Выполнить `/bin/ls` или любую другую без аргументов
    - [x] Выполнить пустую команду
    - [ ] Выполнить команду из пробелов табов
  - [x] Аргументы
    - [x] Выполнить `/bin/ls` или любую другую с аргументами, но без кавычек или двойных кавычек
    - [x] Повторить несколько раз с разными командами и аргументами
  - [x] echo
    - [x] Выполнить команду без флага и с флагом `-n`
    - [x] Повторить несколько раз с разными аргументами
  - [x] exit
    - [x] Выполнить команду с аргументом и без
    - [x] Повторить несколько раз с разными аргументами
  - [x] Возвращение значения процесса
    - [x] Выполнить команду `/bin/ls` или любую другую с аргументами, но без кавычек или двойных кавычек, затем выполните `echo $?`
    - [x] Проверить выведенное значение. Повторить это в bash и сравнить значения.
    - [x] Повторить несколько раз с разными командами и аргументами, попробовать что-то невыполнимое `'/bin/ls sarega4gesrgs`
    - [x] Попробовать $? + $?
    - ![img_13.png](img_13.png)
  - [ ] Сигналы
    - [ ] ctrl-C с пустым промптом должен сделать новую строку с новым промптом
    - [ ] ctrl-\ при пустом промпте ничего не делает
    - [ ] ctrl-D при пустом промпте должен сделать выход из minishell
    - [ ] ctrl-C, когда в промпте уже что-то написано, должен сделать новую строку с пустым промптом
    - [ ] ctrl-D, когда в промпте уже что-то написано, ничего не делает
    - [ ] ctrl-\, когда в промпте уже что-то написано,должен сделать выход из minishell
    - [ ] ctrl-C после выполнения блокирующей команды типа `cat` или `grep` без аргументов
    - [ ] ctrl-\ после выполнения блокирующей команды типа `cat` или `grep` без аргументов
    - [ ] ctrl-D после выполнения блокирующей команды типа `cat` или `grep` без аргументов
  - [x] Двойные кавычки
    - [x] Выполнить простую команду с аргументами, но в этот раз с кавычками (внутри кавычек должны быть пробелы)
    - [x] Выполнить `echo "cat lol.c | cat>lol.c"`
    - [x] Что-нибудь кроме `$`
  - [x] Одинарные кавычки
    - [x] Выполнить команду с одинарными кавычками как аргумент
    - [x] Попробовать пустые аргументы
    - [x] Попробовать переменные окружения, пайпы и редиректы в одинарных кавычках
    - [x] `echo '$USER'` должно показать $USER
  - [x] env
    - [x] Проверить, что env показывает актуальные переменные окруженния
  - [x] export
    - [x] Создать новые переменные окружения, потом изменить значения
  - [x] unset
    - [x] Проверить удаление переменных окружения 
    - [x] Для проверки использоваться env
  - [x] cd
    - [x] Использовать команду и проверить правильность местонахождения командой `/bin/ls`
    - [x] Попробовать несколько раз с работающими и неработающими cd
    - [x] Попробовать 'cd .' и 'cd ..'
    - ![img_8.png](img_8.png)
  - [x] pwd
    - [x] Проверить в разных директориях
  - [x] Относительный путь
    - [x] Выполнить команды с относительным путём
    - [x] Выполнить команды, но без пути (ls, wc)
    - [x] Удалить $PATH и проверить, что ничего больше не выполняется.
    - [x] Установить $PATH и его значение обратно и проверить, что директории проверяются в правильно порядке
  - [ ] Редиректы
    - [x] Выполнить команды с редиректами `<` или `>`
    - [x] Повторить с разными командами и аргументами иногда меняя > на >>
    - [ ] Проверить, что << (не обновляет историю)
  - [ ] Пайпы
    - [ ] Выполнить команды типа `cat file | greb bla | more`
    - [ ] Попробовать что-то невыполнимое типа `ls nrajehkfgewku | grep bla | more`
    - [ ] Попробовать смешать пайпы и редиректы
  - [ ] Разные проверки
    - [ ] Набери команду, потому crtl-C, потом нажать enter. Буфер должен быть пустым и ничего не должно выполниться.
    - [x] Мы можем навигировать в истории с помощью стрелок вверх и вниз
    - [x] Выполнить команды, которые точно не должны выполняться (пример `sklefuhoseufbasl`), шелл не должен сломаться или дать ошибку
    - [ ] Попробуйте выполнить длинную команду с множеством аргументов
  - [ ] Переменные окружения
    - [x] Выполнить echo c любой переменной кружения
    - [x] Проверить, что $ считается переменной окружения
    - [ ] Проверить, что двойные кавычки работают с $
    - [x] Проверьте, что $USER существует или установите его
    - [x] echo "$USER" должно показать значение переменной $USER
 
# todo

- [ ] Return values of a process `$?`

# Выполнение функций влияющих на окружение и их сочетание с пайпом
- [ ] CD 
  - [x] `cd test.txt`
    - неправильная текстовка
      - ![img_10.png](img_10.png)
  - [x] `cd closed_dir` директория закрытая для доступа
    - должно быть ![img_11.png](img_11.png)
    - сейчас так ![img_12.png](img_12.png)
  - [x] `cd .. < test.txt` или `cd .. > test.txt`
    - переходит на директорию выше
    - при `>` или `>>` гарантирован редирект
  - [x] `cd .. | cat`  или `echo loh | cd ..`
    - не переходит на директорию выше
  - [x] `unset HOME`
    - удаляет все значения
  - [x] `export HOME`
    - заменяет все значения
![img_7.png](img_7.png)