using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace Lab2_wb.Controllers
{
    public class ProdusController : Controller
    {
        // GET: Produs
        public ActionResult Index()
        {
            return View();
        }

        public string Product (int param1, int? param2)
        {
            if (!param2.HasValue)
            {
                return "Dati ambii parametrii";
            }
            else
                return (param1 * param2.Value).ToString();
        }
    }
}