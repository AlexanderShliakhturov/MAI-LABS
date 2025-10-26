import numpy as np
import matplotlib.pyplot as plt

# коэффициент теплопроводности (alpha>0)
alpha = 1.0 
# отрезок стержня, для которого составлена задача теплопроводности [0, L]
L = np.pi    
# конечное время
T = 1.0               

def exact_solution(x, t, alpha=alpha):
    return np.exp(-alpha * t) * np.cos(x)

def initial_condition(x):
    return np.cos(x)

def boundary_left(t, alpha=alpha):
    return np.exp(-alpha * t)

def boundary_right(t, alpha=alpha):
    return -np.exp(-alpha * t)

#метод прогонки из лр1 для решения трехдиагональной СЛАУ
def progonka(a, b, c, d):
    
    n = len(d)
    
    P = np.zeros(n-1)  
    Q = np.zeros(n)    
    
    # P[0] = c[0] / b[0] 
    P[0] = -c[0] / b[0]     
    Q[0] = d[0] / b[0]  
    
    for i in range(1, n-1):

        P[i] = -c[i] / (b[i] + a[i-1] * P[i-1])
        Q[i] = (d[i] - a[i-1] * Q[i-1]) / (b[i] + a[i-1] * P[i-1])

    #P[n-1] = 0 потому что последний коэффициент c равен нулю
    Q[n-1] = (d[n-1] - a[n-2] * Q[n-2]) / (b[n-1] + a[n-2] * P[n-2])

    x = np.zeros(n)
    # x[n-1] = Q[n-1] потому что P[n-1] = 0, т.е остается только свободный член
    x[n-1] = Q[n-1]
    
    #мы знаем последний икс. Через него теперь вычислим предпоследний, итд
    for i in range(n-2, -1, -1):
        # x[i] = Q[i] - P[i] * x[i+1]
        x[i] = Q[i] + P[i] * x[i+1]
    
    return x

def apply_boundary_conditions(u, dx, t, alpha, bc_approx="two_point_first"):
    """
    Аппроксимирует граничные условия по выбранной схеме.
    Поддерживаются варианты:
      - two_point_first
      - three_point_second
      - two_point_second
    """
    # Коэффициенты задачи Робена (для Дирихле b=0)
    a_left, b_left = 1.0, 0.0
    a_right, b_right = 1.0, 0.0
    c_left = boundary_left(t, alpha)
    c_right = boundary_right(t, alpha)

    if bc_approx == "two_point_first":
        # du/dx ≈ (u1 - u0)/dx
        u[0] = (c_left - (b_left/dx)*u[1]) / (a_left - b_left/dx)
        u[-1] = (c_right + (b_right/dx)*u[-2]) / (a_right + b_right/dx)

    elif bc_approx == "three_point_second":
        # du/dx ≈ (-3u0 + 4u1 - u2)/(2dx)
        u[0] = (c_left - b_left*(4*u[1] - u[2])/(2*dx)) / (a_left - 3*b_left/(2*dx))
        u[-1] = (c_right - b_right*(-4*u[-2] + u[-3])/(2*dx)) / (a_right + 3*b_right/(2*dx))

    elif bc_approx == "two_point_second":
        # du/dx ≈ (u1 - u_-1)/(2dx), требуется фиктивный узел
        if b_left != 0:
            u_minus1 = u[1] - 2*dx*(c_left - a_left*u[0])/b_left
        else:
            u_minus1 = u[0]
        if b_right != 0:
            u_plus1 = u[-2] + 2*dx*(c_right - a_right*u[-1])/b_right
        else:
            u_plus1 = u[-1]
        # здесь просто возвращаем u, фиктивные узлы могут использоваться внутри матрицы при необходимости
    else:
        raise ValueError("Неизвестный тип аппроксимации граничных условий")

    return u

def compute_errors(u_num, x, t, alpha=alpha):
    u_ex = exact_solution(x, t, alpha)
    err_max = np.max(np.abs(u_num - u_ex))
    err_L2 = np.sqrt(np.sum((u_num - u_ex)**2) * (x[1]-x[0])) 
    return err_max, err_L2


#Nx, Nt - число интервалов по времени и по координате x 
def explicit_scheme(Nx, Nt, T, alpha):
    #определяем шаги по времени и по координате x
    dx = L / Nx
    dt = T / Nt
    
    #предупреждение о возможной нестабильности решения
    r = alpha * dt / dx**2
    if r > 0.5:
        print("Warning: explicit scheme unstable if r>0.5; current r =", r)
        
    # после разбиения получаем N+1 узел разбиения времени и координаты
    x = np.linspace(0, L, Nx+1)
    t_grid = np.linspace(0, T, Nt+1)

    # формируем массив значений на текущем временном слое. Изначально на основе начальных условий
    u = initial_condition(x)
    # Уточняем граничными условиями
    u[0] = boundary_left(0, alpha)
    u[-1] = boundary_right(0, alpha)

    #на каждом временном шаге
    for n in range(Nt):
        
        #берем очередной промежуток времени
        t_np1 = t_grid[n+1]
        u_new = u.copy()

        # вычисляем значение функции на временном слое для внутренних узлов        
        # u_i_n+1 = u_i_n + r(u_i+1_n - 2u_i_n + u_i-1_n), где r = a*dt/dx^2
        u_new[1:-1] = u[1:-1] + r*(u[2:] - 2*u[1:-1] + u[:-2])
        
        # граничные условия (время t_np1)
        #устанавлиеваем краевые значения в соответствии с условиями
        u_new[0] = boundary_left(t_np1, alpha)
        u_new[-1] = boundary_right(t_np1, alpha)
        u = u_new
    
    # вернем массивы: разбиение по x, разбиение по времени, значения функции
    return x, t_grid, u

def implicit_scheme(Nx, Nt, T, alpha):

    #получаем разбиение аналогично явной схеме
    dx = L / Nx
    dt = T / Nt
    r = alpha * dt / dx**2
    x = np.linspace(0, L, Nx+1)
    t_grid = np.linspace(0, T, Nt+1)

    # число внутренних узлов
    n_in = Nx - 1
    
    # поддиагональные элементы
    a = -r * np.ones(n_in-1)
    # диагональные
    b = (1 + 2*r) * np.ones(n_in)
    # наддиагональные
    c = -r * np.ones(n_in-1)

    # initial
    u = initial_condition(x)
    u[0] = boundary_left(0, alpha)
    u[-1] = boundary_right(0, alpha)

    for n in range(Nt):
        
        t_np1 = t_grid[n+1]
        d = u[1:-1].copy()
        d[0] += r * boundary_left(t_np1, alpha)
        d[-1] += r * boundary_right(t_np1, alpha)

        # Решаем СЛАУ методом прогонки
        u_in = progonka(a, b, c, d)
        u[1:-1] = u_in
        # Подставляем граничные значения
        u[0] = boundary_left(t_np1, alpha)
        u[-1] = boundary_right(t_np1, alpha)
        
    # вернем массивы: разбиение по x, разбиение по времени, значения функции
    return x, t_grid, u

def crank_nicolson_scheme(Nx, Nt, T, alpha):
    
    # Создаем разбиение
    dx = L / Nx
    dt = T / Nt
    r = alpha * dt / (2 * dx**2)
    x = np.linspace(0, L, Nx+1)
    t_grid = np.linspace(0, T, Nt+1)

    #вписываем начальные и граничные условия
    u = np.zeros(Nx+1)
    u[:] = initial_condition(x)
    u[0] = boundary_left(0, alpha)
    u[-1] = boundary_right(0, alpha)

    #число внутренних узлов
    n_in = Nx - 1

    # коэффициенты для трехдиагональной матрицы A
    a = -r * np.ones(n_in-1)
    b = (1 + 2*r) * np.ones(n_in)
    c = -r * np.ones(n_in-1)

    # коэффициенты для трехдиагональной матрицы B
    aB = r * np.ones(n_in-1)
    bB = (1 - 2*r) * np.ones(n_in)
    cB = r * np.ones(n_in-1)

    # в цикле решаем систему Au_n+1 = Bu_n + вклад граничных условий
    for n in range(Nt):
        t_n = t_grid[n]
        t_np1 = t_grid[n+1]

        u_in = u[1:-1]

        # формируем правую часть B * u^n + вклад граничных условий
        d = np.zeros_like(u_in)
        # Внутренние узлы
        for i in range(1, n_in-1):
            d[i] = aB[i-1]*u_in[i-1] + bB[i]*u_in[i] + cB[i]*u_in[i+1]
        # Первый и последний внутренние узлы
        d[0] = bB[0]*u_in[0] + cB[0]*u_in[1]
        d[-1] = aB[-1]*u_in[-2] + bB[-1]*u_in[-1]

        # учёт граничных условий с двух временных слоёв
        left_now = boundary_left(t_n, alpha)
        right_now = boundary_right(t_n, alpha)
        left_next = boundary_left(t_np1, alpha)
        right_next = boundary_right(t_np1, alpha)

        d[0] += r * (left_next + left_now)
        d[-1] += r * (right_next + right_now)

        # решаем систему методом прогонки
        u_in_next = progonka(a, b, c, d)

        # обновляем решение
        u[1:-1] = u_in_next
        u[0] = left_next
        u[-1] = right_next

    return x, t_grid, u

def refinement_study(scheme_fn, Nx_list, T, alpha, dt_formula='stable', Nt_manual=None):

    dx_list = []
    err_max_list = []
    err_L2_list = []

    for Nx in Nx_list:
        dx = L / Nx
        if dt_formula == 'stable':
            dt = 0.45 * dx**2 / alpha
            Nt = int(np.ceil(T / dt))
            dt = T / Nt
        elif dt_formula == 'dt_proportional_dx2':
            dt = dx**2 / alpha
            Nt = int(np.ceil(T / dt))
            dt = T / Nt
        elif dt_formula == 'fixed':
            if Nt_manual is None:
                raise ValueError("Provide Nt_manual for fixed dt_formula")
            Nt = Nt_manual
        else:
            raise ValueError("Unknown dt_formula")

        # run scheme
        x, t_grid, u_num = scheme_fn(Nx, Nt, T, alpha)
        err_max, err_L2 = compute_errors(u_num, x, T, alpha)
        dx_list.append(dx)
        err_max_list.append(err_max)
        err_L2_list.append(err_L2)
        print(f"Nx={Nx:4d}, dx={dx:.5e}, Nt={Nt:6d}, err_max={err_max:.3e}, err_L2={err_L2:.3e}")
    return np.array(dx_list), np.array(err_max_list), np.array(err_L2_list)

if __name__ == "__main__":
    # параметры
    alpha = 1.0
    
    t_range = [0.25, 0.5, 1, 2]

    for T in t_range:
        # сетка по x
        Nx = 50
        dx = L / Nx
        
        # для явной схемы выберем dt по условию устойчивости
        dt_explicit = 0.5 * dx**2 / alpha
        Nt_explicit = int(np.ceil(T / dt_explicit))
        
        dt_explicit = T / Nt_explicit
        print("Explicit: dx=", dx, "dt=", dt_explicit, "r=", alpha*dt_explicit/dx**2)

        # Запуск схем
        x_e, t_e, u_e = explicit_scheme(Nx, Nt_explicit, T, alpha)
        x_i, t_i, u_i = implicit_scheme(Nx, Nt_explicit, T, alpha)
        x_cn, t_cn, u_cn = crank_nicolson_scheme(Nx, Nt_explicit, T, alpha)

        # аналитическое решение
        u_ex = exact_solution(x_e, T, alpha)

        # вычисление ошибок
        err_e_max, err_e_L2 = compute_errors(u_e, x_e, T, alpha)
        err_i_max, err_i_L2 = compute_errors(u_i, x_i, T, alpha)
        err_cn_max, err_cn_L2 = compute_errors(u_cn, x_cn, T, alpha)

        print("\nErrors at t = {:.3f}:".format(T))
        print(f"Explicit:    max={err_e_max:.3e}, L2={err_e_L2:.3e}")
        print(f"Implicit BE:  max={err_i_max:.3e}, L2={err_i_L2:.3e}")
        print(f"Crank-Nicolson: max={err_cn_max:.3e}, L2={err_cn_L2:.3e}")

        # График сравнений в конечный момент
        plt.figure(figsize=(8,5))
        plt.plot(x_e, u_ex, label='Exact', linewidth=2)
        plt.plot(x_e, u_e, '--', label='Explicit')
        plt.plot(x_i, u_i, ':', label='Implicit BE')
        plt.plot(x_cn, u_cn, '-.', label='Crank-Nicolson')
        plt.legend()
        plt.xlabel('x')
        plt.ylabel('u(x,T)')
        plt.title(f'Comparison at t={T:.3f}')
        plt.grid(True)
        # plt.show()
        plt.savefig(f"comparison for t={T}.png")

        # Проведём исследование со сжатием сетки
        Nx_list = [20, 40, 80, 160]
        print("\n--- Experiment: Explicit ---")
        dxs_e, errs_e_max, errs_e_L2 = refinement_study(explicit_scheme, Nx_list, T, alpha, dt_formula='stable')
        print("\n--- Experiment study: Implicit ")
        dxs_i, errs_i_max, errs_i_L2 = refinement_study(implicit_scheme, Nx_list, T, alpha, dt_formula='dt_proportional_dx2')
        print("\n--- Experiment study: Crank-Nicolson")
        dxs_cn, errs_cn_max, errs_cn_L2 = refinement_study(crank_nicolson_scheme, Nx_list, T, alpha, dt_formula='dt_proportional_dx2')

        # Лог-лог графики для оценки порядка сходимости
        plt.figure(figsize=(8,5))
        plt.loglog(dxs_e, errs_e_max, 'o-', label='Explicit max')
        plt.loglog(dxs_i, errs_i_max, 's-', label='Implicit BE max')
        plt.loglog(dxs_cn, errs_cn_max, 'd-', label='Crank-Nicolson max')
        plt.xlabel('dx')
        plt.ylabel('max error')
        plt.legend()
        plt.grid(True, which="both")
        plt.title(f'max norm errors for t={T}')
        plt.show()
        plt.savefig(f"errors for t={T}.png")
