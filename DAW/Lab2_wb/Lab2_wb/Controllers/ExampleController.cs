using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace Lab2_wb.Controllers
{
    public class ExampleController : Controller
    {
        // GET: Example
        public ActionResult Index()
        {
            return View();
        }

        public string Concatenare(string param1, string param2) => param1 + ' ' + param2;

        public string Operatie (int? param1, string param2, int? param3)
        {
            if (!param1.HasValue)
            {
                return "Dati parametrul 1";
            }
            if (param2 == null)
            {
                return "Dati parametrul 2";
            }
            if (!param3.HasValue)
            {
                return "Dati parametrul 3";
            }

            switch (param2)
            {
                case "plus":
                    return (param1.Value + param3.Value).ToString();
                case "minus":
                    return (param1.Value - param3.Value).ToString();
                case "ori":
                    return (param1.Value * param3.Value).ToString();
                case "div":
                    return (param1.Value / param3.Value).ToString();
                default:
                    return "Parametru 2 nu are sens";
            }
        }
    }
}