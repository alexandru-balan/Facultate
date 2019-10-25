using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using System.Text.RegularExpressions;

namespace Lab2_wb.Controllers
{
    public class SearchController : Controller
    {
        // GET: Search
        public ActionResult Index()
        {
            return View();
        }

        public string Telefon (string tel)
        {
            if (tel == null)
            {
                return "Dati telefonul";
            }

            return "Fine";
        }

        public string CNP (string cnp)
        {
            if (cnp == null)
            {
                return "Dati telefonul";
            }

            return "Fine";
        }
    }
}