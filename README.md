# cmd_terminal
Простой обработчик терминальных команд

Пример листинг работы:
>help
      help - команда предназначена для вывода в терминал справки 
     reset - команда перезапуска контроллера 
       led - команда управления светодиодом 
>help help

 справочная информация по команде help

  команда предназначена для вывода на экран справочной информации 
  по командам терминала.
  формат команды: >help <STRING> 
   all - вывод краткой справки по всем командам, 
   <STRING> - вывод на экран полной информации о команде, 
   мненомика которой указана в поле STRING.

>help led

 справочная информация по команде led

  команда предназначена для установки режима работы светодиода.
  формат команды: >led <STRING> 
   on - светодиод включен, 
   off - светодиод выключен.

>help reset

 справочная информация по команде reset

  команда предназначена для програмного перезапуска микроконтроллера.
  формат команды: >reset <NONE> 


>led on
Включен светодиод
>led off
Выключен светодиод
