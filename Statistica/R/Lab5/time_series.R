#internet-traffic-data-in-bits-fr.csv

fram <- read.csv("/home/nick/Projects/R/Lab5/data.csv")

data <- ts(fram$data,#возьмем столбец, который с названием data
   start = c(1973, 1), # с 73 года, 1 месяца
   frequency = 12 #12 месяцев
)

#(«auto-correlation function», ACF) выводит коэффици
#енты автокорреляции и рисует график автокорреляции
#чем больше палочек выходит за полоски, 
#тем более значима периодичность
#
#plot(data)
acf(data, main="")

#То, что волнообразный график пиков как бы затухает, 
#говорит о том, 
#что в наших данных возможен тренд. Проверим это
#STL — «Seasonal Decomposition of Time Series
#by Loess»), которая вычленяет из временного ряда три компоненты:
#сезонную (в данном случае суточную), тренд и случайную, при помощи
#сглаживания данных методом LOESS.
plot(stl(data, s.window="periodic")$time.series, main="")


#Здесь нам короче надо найти номер элемента
#При котором значение будет минимально
#Считать будет долго

#считает дольше с каждой цифрой, 
#но опытным путем выяснено, что в моей подборке
#минимальное значение будет на индексе 15

#AIC (Akaike’s Information Criterion) 
#информационный критерий Акаике. Это критерий, который позволяет сравнивать
#модели между собой (несколько подробнее про AIC рассказано в главе
# про временные ряды). Чем меньше AIC, тем лучше модель.
mini = 100500
minInd = 0
first <- arima(data, order=c(0,0,1))
for (m in 1:16)#должно быть 1:length(data)
{
     mm <- arima(data, order=c(0,0,m))
     cur = AIC(mm)
     if(cur < mini){
       minInd = m
       mini = cur
       first <- mm
     }
     print(m)
     print(cur)
}
minInd
#делаем то же самое, подставляя в вектор в 3 значение 
# минимального номера из прошлого цикла (15 у меня), 
# ищем 1
# это будет лаг авторегресии
second <- arima(data, order=c(1,0,minInd))
mini <- 100500
errCount <- 0
for (m in 1:13)#должно быть 1:length(data)
{
  a <- try(arima(data, order=c(m,0,minInd)))
  if(class(a) == "try-error"){ 
    errCount <- errCount + 1
    next
  }
  cur = AIC(a)
  if(cur < mini){
    minInd = m
    mini = cur
    second <- a
  }
  print(m)
  print(cur)
}


# лаг будет на 12  индексе (видимо типа как раз год на моих данных)

# то же самое для второго столбца

mini <- 100500
errCount <- 0
third <- arima(data, order=c(12,0,15))
for (m in 1:6)
{
  a <- try(arima(data, order=c(12,m,15)))
  if(class(a) == "try-error"){ 
    errCount <- errCount + 1
    next
  }
  cur = AIC(a)
  if(cur < mini){
    minInd = m
    mini = cur
    third <- a
  }
  print(m)
  print(cur)
}

#Вышло короче 4, при 21 эксепшене лол

#в third теперь оптимус типа

plot(data, xlim=c(1973,1981), ylim=c(min(data)-10000,max(data)))

#зелёным будет линия прогноза
#на 12 месяцев
lines(predict(third, n.ahead=12, se.fit = TRUE)$pred, col="green")
# верхняя линия прогноза
lines(predict(third, 
              n.ahead=12, 
              se.fit = TRUE)$se +
      predict(third, n.ahead=12, se.fit = TRUE)$pred,
      col="red")
# нижняя
lines(-predict(third, n.ahead=12, se.fit = TRUE)$se +
       predict(third, n.ahead=12, se.fit = TRUE)$pred,
       col="blue")
#plot(AIC(tst), type="b")


# Максимальное и минимальное ожидаемое количество  умерших:
# Максимум
round(predict(third,
              n.ahead=12, # период прогноза
              se.fit = TRUE)$se + # берем из объекта только ошибку
              predict(third, # складываем ошибку и данные прогноза
              n.ahead=12,
              se.fit = TRUE)$pred) # берем только данные самого прогноза
# Минимум
round(-predict(third, n.ahead=12, se.fit = TRUE)$se +
      predict(third, n.ahead=12, se.fit = TRUE)$pred)


library("forecast", lib.loc="~/R/x86_64-pc-linux-gnu-library/3.2")
library("tseries", lib.loc="~/R/x86_64-pc-linux-gnu-library/3.2")

plot(forecast(third))
adf.test(data, alternative="stationary", k=12)
