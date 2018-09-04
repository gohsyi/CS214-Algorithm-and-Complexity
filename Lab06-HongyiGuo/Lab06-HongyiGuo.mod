/*********************************************
 * OPL 12.8.0.0 Model
 * Author: guoho
 * Creation Date: Apr 14, 2018 at 5:01:45 PM
 *********************************************/
{string} Products = ...;
{string} Resources = ...;

range Months = 1..6;

float Time[Resources][Products] = ...;
int Limitations[Months][Products] = ...;
int Profits[Products] = ...;
int Num[Resources] = ...;
float StoreCost = ...;
float WorkingHoursPerMonth = ...;
int FinalStock = ...;
int StockLimitation = ...;

dvar int+ totalProfit;
dvar int+ sellProfit;
dvar int+ holdingCost;
dvar int+ make[Months][Products];
dvar int+ sell[Months][Products];
dvar int+ hold[Months][Products];
dvar int+ total[Months][Products];
dvar int+ usage[Months][Resources];
dvar float+ working_time[Months][Resources];



maximize totalProfit;


subject to {

sellProfit == sum(p in Products) sum(m in Months) (sell[m][p] * Profits[p]);
holdingCost == sum(p in Products) sum(m in Months) (hold[m][p] * StoreCost);
totalProfit == sellProfit - holdingCost;

workingTime:
/*
	forall(m in Months)
	  (sum(p in Products) sum(r in Resources) Time[r][p] * make[m][p]) <= WorkingHoursPerMonth;
*/

	forall(m in Months)
	  forall(r in Resources)
	    working_time[m][r] == (sum(p in Products) Time[r][p] * make[m][p]);
	forall(m in Months)
	  forall(r in Resources)
	    working_time[m][r] <= Num[r] * WorkingHoursPerMonth;


sellAndHold:
	forall(m in Months)
	  forall(p in Products) {
	  	total[m][p] == make[m][p] + (m == 1 ? 0 : hold[m-1][p]);
	    sell[m][p] <= Limitations[m][p] && sell[m][p] <= total[m][p];
	    hold[m][p] == total[m][p] - sell[m][p];
	    hold[m][p] <= StockLimitation;
   	  }
	
finalStock:
	forall(p in Products) hold[6][p] == 50;
	
maintenance:
	forall(r in Resources)
	  forall(m in Months) {
	    working_time[m][r] == 0 
	    	=> usage[m][r] == 0;
	    (working_time[m][r] >= 0.01 && working_time[m][r] <= WorkingHoursPerMonth) 
	    	=> usage[m][r] == 1;
	    (working_time[m][r] >= WorkingHoursPerMonth*1+0.01 && working_time[m][r] <= WorkingHoursPerMonth*2)
	    	=> usage[m][r] == 2;
	    (working_time[m][r] >= WorkingHoursPerMonth*2+0.01 && working_time[m][r] <= WorkingHoursPerMonth*3) 
	    	=> usage[m][r] == 3;
	    (working_time[m][r] >= WorkingHoursPerMonth*3+0.01 && working_time[m][r] <= WorkingHoursPerMonth*4) 
	    	=> usage[m][r] == 4;
   	  }
   	  
	forall(r in Resources)
	  (sum(m in Months) usage[m][r]) <= 5 * Num[r];
}
