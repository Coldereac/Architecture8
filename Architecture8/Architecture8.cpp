
#include <iostream>

int main()
{
    int8_t a = -16; //змінні з числами для рахування
    int8_t b = -15;
    int16_t res, res1; //збереження результату
    __asm {
        mov al, a //надаємо регістру al значення a
        cmp al, b //порівнюємо al та b
        je _equal //в залежності від результата переходимо до потрібної мітки
        jl _lower
        jg _greater

        _equal: //a=b
            mov res, -2 //надаємо результату значення -2
            jmp _exitt //перехід до виходу

        _greater: // a>b
            sal al, 1 //множимо al на 2 та зберігаємо результат в al
            cbw //розширюємо al до ax
            mov cx, ax //переносимо ax до cx, щоб перемістити інше значення в al і розширити до ax
            mov al, b //надаємо регістру al значення b
            cbw //розширюємо al до ax
            add cx, ax // додаємо до cx ax і зберігаємо результат в cx
            mov res, cx // надаємо res значення cx
            jmp _exitt //перехід до виходу

        _lower:
            mov cl, al // тимчасово надаємо регістру cl значення al
            mov al, b // надаємо регістру al значення b
            cbw //розширюємо al до ax
            mov bx, ax // надаємо регістру bx значення ax
            mov al, cl //повертаємо значення al назад
            sub al, 5 // віднімаємо від al 5 і зберігаємо результат в al
            cbw  //розширюємо al до ax
            cwd  //розширюємо ax до ax:dx
            idiv bx // ділимо ax:dx на bx
            mov res, ax // надаємо res значення ax
            mov res1, dx // надаємо res1 значення dx
            jmp _exitt
        
        _exitt: //вихід
            mov ax, 4C00h; //стандартна команда DOS
    }
    if (a < b) //виведення результату
    {
        std::cout << "quotient: " << res << "\n";
        std::cout << "remainder: " << res1 << "\n";
    }
    else
    {
        std::cout << "result: " << res << "\n";
    }
    return 0;
}

